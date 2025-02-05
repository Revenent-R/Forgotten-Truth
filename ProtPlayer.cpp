// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "Fragments.h"
#include "InteractableDoors.h"
#include "InteractableDrawer.h"
#include "Flashlight.h"
#include "MyKey.h"
#include "Battery.h"
#include "Pills.h"

FTimerHandle InspectTimer;
FTimerHandle CutSceneTimer;
FTimerHandle DisableTimer;

// Sets default values
AProtPlayer::AProtPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetMesh());
	//FlashLight = CreateDefaultSubobject<UStaticMeshComponent>("FlashLight");
	//FlashLight->SetupAttachment(GetMesh());
	//Light = CreateDefaultSubobject<USpotLightComponent>("Light");
	//Light->SetupAttachment(FlashLight);

	GetMesh()->CastShadow = false;
	//FlashLight->CastShadow = false;

	bUseControllerRotationPitch = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	FragmentPicked = false;
	Range = 500.0f;
	InterpSpeed = 5600.0f;
	Paranoia = 0.0f;
	PillsAmount = 0;
	Power = 1.0f;

	isOn = false;
	InputEnabled = false;
	//Light->SetIntensity(0.0f);
	Drain = 0.01f;

	TimerT = 15.0f;
	Timer = 0.0f;
	Index = 0;
	SprintPower = 1.0f;

	hasFlashlight = false;


}

// Called when the game starts or when spawned
void AProtPlayer::BeginPlay()
{
	Super::BeginPlay();

	StartCutScene();

	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false);
	//FlashLight->AttachToComponent(GetMesh(), rules, FName("LeftHandSocket"));
	Camera->AttachToComponent(GetMesh(), rules, FName("HeadSocket"));


}

// Called every frame
void AProtPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isOn) {
		if (Flash != nullptr) {
			if (Power > 0.0f) {
				Power -= (Drain * DeltaTime);
			}
			else {
				ChangeFlashLightState();
			}
		}
	}

	if (!Sprinting) {
		if (SprintPower < 1.0f) {
			SprintPower += (0.1f * GetWorld()->GetDeltaSeconds());
		}
	}

	IdleTimer(DeltaTime);

}

// Called to bind functionality to input
void AProtPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProtPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProtPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AProtPlayer::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AProtPlayer::LookUp);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AProtPlayer::StartFragmentPick);
	PlayerInputComponent->BindAction("PickPills", IE_Pressed, this, &AProtPlayer::PickupPills);
	PlayerInputComponent->BindAction("ConsumePills", IE_Pressed, this, &AProtPlayer::ConsumePills);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AProtPlayer::Interact);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AProtPlayer::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AProtPlayer::StopJumping);
	PlayerInputComponent->BindAction("TurnOn", IE_Pressed, this, &AProtPlayer::ChangeFlashLightState);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AProtPlayer::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AProtPlayer::StopSprint);
	PlayerInputComponent->BindAction("PickFlash", IE_Pressed, this, &AProtPlayer::PickUpFlashLight);

}

void AProtPlayer::MoveForward(float val)
{
	if (InputEnabled) {
		if (!FragmentPicked) {
			AddMovementInput(GetActorForwardVector(), val);
		}
	}
}

void AProtPlayer::MoveRight(float val)
{
	if (InputEnabled) {
		if (!FragmentPicked) {
			//if (val > 0) { mRight = true; }
			//if (val < 0) { mRight = false; }
			RL = val;
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f * GetWorld()->GetDeltaSeconds(), FColor::Red, FString::Printf(TEXT("%d"), RL));
			AddMovementInput(GetActorRightVector(), val);
		}
	}
}

void AProtPlayer::Turn(float val)
{
	if (InputEnabled) {
		if (!FragmentPicked) {
			AddControllerYawInput(val);
		}
		else {
			if (Memory != nullptr) {
				Memory->AddActorWorldRotation(FRotator(0.0f, val, 0.0f));
			}
		}
	}
}

void AProtPlayer::LookUp(float val)
{
	if (InputEnabled) {
		if (!FragmentPicked) {
			AddControllerPitchInput(val);
		}
		else {
			if (Memory != nullptr) {
				Memory->AddActorWorldRotation(FRotator(val, 0.0f, 0.0f));
			}
		}
	}
}

void AProtPlayer::Jump()
{
	if (InputEnabled) {
		ACharacter::Jump();
		Jumping = true;
	}
}

void AProtPlayer::StopJumping()
{
	if (InputEnabled) {
		ACharacter::StopJumping();
		Jumping = false;
	}
}

void AProtPlayer::IdleTimer(float DeltaTime)
{
	if (GetVelocity().Length() <= 0) {
		Timer += 1.0f * DeltaTime;
		if (Timer >= TimerT) {
			Index = 1;
		}
	}
	else {
		Timer = 0;
		Index = 0;
	}
}

void AProtPlayer::StartFragmentPick()
{
	if (!FragmentPicked) {
		FHitResult Hit;
		FVector Start = Camera->GetComponentLocation();
		FVector End = Start + (Camera->GetForwardVector() * Range);
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, params)) {
			Memory = Cast<AFragments>(Hit.GetActor());
			if (Memory != nullptr) {
				Memory->Fragment->SetSimulatePhysics(false);
				Memory->Light->SetIntensity(0.0f);
				UGameplayStatics::PlaySound2D(GetWorld(), Memory->PaperSound, 1.0f, 1.0f, 0.0f, nullptr, Memory);
				Memory->StopPulsate();
				FTimerDelegate Del;
				Del.BindUFunction(this, FName("FragmentPickUp"), Memory);
				GetWorldTimerManager().SetTimer(InspectTimer, Del, 0.3f, true);
			}
		}
	}
	if (FragmentPicked) {
		FHitResult Hit;
		FVector Start = Camera->GetComponentLocation();
		FVector End = Start + (Camera->GetForwardVector() * Range);
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, params)) {
			Memory = Cast<AFragments>(Hit.GetActor());
			if (Memory != nullptr) {
				Memory->Fragment->SetSimulatePhysics(true);
				Memory->HUDWidget->SetVisibility(true);
				if (Memory->Last) {
					APlayerController* PC = Cast<APlayerController>(GetController());
					UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);
				}
				FragmentPicked = false;
				//Memory->Fragment->AddImpulse(-Memory->Fragment->GetForwardVector() * 100.0f);
			}
		}
	}
}

void AProtPlayer::FragmentPickUp(AFragments* PickedFragment)
{
	if (PickedFragment != nullptr) {
		FVector Target = Camera->GetComponentLocation() + (Camera->GetForwardVector() * 80.0f);
		PickedFragment->SetActorLocation(FMath::VInterpTo(PickedFragment->GetActorLocation(), Target, GetWorld()->GetDeltaSeconds(), InterpSpeed * GetWorld()->GetDeltaSeconds()));
		PickedFragment->SetActorRotation(FMath::RInterpTo(PickedFragment->GetActorRotation(), Camera->GetComponentRotation(), GetWorld()->GetDeltaSeconds(), InterpSpeed * GetWorld()->GetDeltaSeconds()));
		if (FVector::Dist(PickedFragment->GetActorLocation(), Target) <= 1.0f) {
			PickedFragment->AddActorLocalRotation(FRotator(0.0f, 180.0f, 0.0f));
			FragmentPicked = true;
			PickedFragment->HUDWidget->SetVisibility(false);
			GetWorldTimerManager().ClearTimer(InspectTimer);
		}
	}
}

void AProtPlayer::PickupPills()
{
	FHitResult Hit;
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * Range);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, params);
	FHitResult NHit;
	FCollisionShape Rec = FCollisionShape::MakeBox(FVector(70.0f, 70.0f, 70.0f));
	if (GetWorld()->SweepSingleByChannel(NHit, Hit.Location, Hit.Location, FRotator(0.0f, 0.0f, 0.0f).Quaternion(), ECC_Visibility, Rec, params)) {
		APills* Pill = Cast<APills>(NHit.GetActor());
		ABattery* Batt = Cast<ABattery>(NHit.GetActor());
		AMyKey* Key = Cast<AMyKey>(NHit.GetActor());
		if (Pill != nullptr) {
			PillsAmount++;
			Heal = Pill->HealingPower;
			Pill->Destroy();
		}
		if (Batt != nullptr) {
			BatteryAmount++;
			Power += Batt->Power;
			Batt->Destroy();
		}
		if (Key != nullptr) {
			hasKey = true;
			Key->Destroy();
		}
	}
}

void AProtPlayer::ConsumePills()
{
	if (PillsAmount > 0) {
		if (Paranoia > Heal) {
			Paranoia -= Heal;
		}
		else {
			Paranoia = 0;
		}
		PillsAmount--;
	}
}

void AProtPlayer::PickUpFlashLight()
{
	if (Flash == nullptr) {
		FHitResult Hit;
		FVector Start = Camera->GetComponentLocation();
		FVector End = Start + (Camera->GetForwardVector() * Range);
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		if (Flash != nullptr) {
			params.AddIgnoredActor(Flash);
		}
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, params);
		FHitResult NHit;
		FCollisionShape Rec = FCollisionShape::MakeBox(FVector(50.0f, 50.0f, 50.0f));
		if (GetWorld()->SweepSingleByChannel(NHit, Hit.Location, Hit.Location, FRotator(0.0f, 0.0f, 0.0f).Quaternion(), ECC_Visibility, Rec, params)) {
			Flash = Cast<AFlashlight>(NHit.GetActor());
			if (Flash != nullptr) {
				Flash->FlashLight->SetSimulatePhysics(false);
				FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
				Flash->AttachToComponent(GetMesh(), rules, FName("LeftHandSocket"));
				Flash->Light->SetIntensity(0.0f);
				Flash->HUDWidget->SetVisibility(false);
				hasFlashlight = true;
			}
		}
	}
}

void AProtPlayer::Interact()
{
	FHitResult Hit;
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * Range);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, params)) {
		AInteractableDoors* Door = Cast<AInteractableDoors>(Hit.GetActor());
		AInteractableDrawer* Drawer = Cast<AInteractableDrawer>(Hit.GetActor());
		if (Door != nullptr) {
			//InteractTimer.Invalidate();
			//DelDo.BindUFunction(Door, FName("ChangeDoorState"));
			Door->Ref = this;
			if (hasKey) {
				Door->isLocked = false;
			}
			if (!InteractTimer.IsValid()) {
				GetWorldTimerManager().SetTimer(InteractTimer, Door, &AInteractableDoors::ChangeDoorState, 0.1f, true);
			}
		}
		if (Drawer != nullptr) {
			//InteractDrTimer.Invalidate();
			//DelDr.BindUFunction(Drawer, FName("ChangeDrawerState"), InteractDrTimer);
			Drawer->Ref = this;
			if (!InteractDrTimer.IsValid()) {
				GetWorldTimerManager().SetTimer(InteractDrTimer, Drawer, &AInteractableDrawer::ChangeDrawerState, 0.1f, true);
			}
		}
	}
}

void AProtPlayer::Sprint()
{
	if (InputEnabled) {
		GetCharacterMovement()->MaxWalkSpeed = 700.0f;
		Sprinting = true;
		SprintPower -= (0.3f * GetWorld()->GetDeltaSeconds());
	}
}

void AProtPlayer::StopSprint()
{
	if (InputEnabled) {
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		Sprinting = false;
	}
}

void AProtPlayer::StartCutScene()
{
	GetMesh()->PlayAnimation(CutScene, false);
	GetWorldTimerManager().SetTimer(CutSceneTimer, this, &AProtPlayer::StopCutScene, 0.02f, true);
}

void AProtPlayer::StopCutScene()
{
	if (!GetMesh()->IsPlaying()) {
		GetWorldTimerManager().ClearTimer(CutSceneTimer);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		InputEnabled = true;
		GetMesh()->CastShadow = true;
		//FlashLight->CastShadow = true;
		Audio = UGameplayStatics::SpawnSound2D(GetWorld(), BackSound, 0.6f);
	}
}

void AProtPlayer::ChangeFlashLightState()
{
	if (InputEnabled) {
		if (isOn) {
			if (Flash != nullptr) {
				Flash->Light->SetIntensity(0.0f);
			}
		}
		else {
			if (Power > 0.0f) {
				if (Flash != nullptr) {
					Flash->Light->SetIntensity(1000.0f);
				}
			}
		}
		isOn = !isOn;
	}
}

