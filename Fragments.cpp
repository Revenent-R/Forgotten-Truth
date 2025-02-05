// Fill out your copyright notice in the Description page of Project Settings.


#include "Fragments.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProtPlayer.h"

// Sets default values
AFragments::AFragments()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Fragment = CreateDefaultSubobject<UStaticMeshComponent>("Fragment");
	SetRootComponent(Fragment);
	Box = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	Box->SetupAttachment(Fragment);
	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	Text->SetupAttachment(Fragment);
	Light = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	Light->SetupAttachment(Fragment);
	HUDWidget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	HUDWidget->SetupAttachment(Fragment);
	
	HUDWidget->SetVisibility(false);

	HUDWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	Box->SetWorldScale3D(FVector(4.75f, 5.5f, 5.75f));

	HUDWidget->SetDrawSize(FVector2D(140.0f, 100.0f));

	HUDWidget->SetWidgetSpace(EWidgetSpace::Screen);

	Text->SetTextRenderColor(FColor::Black);

	Fragment->SetSimulatePhysics(true);

	reachedMin = false;
	LightCSpeed = 5000.0f;
	maxIntensity = 80.0f;
	minIntensity = 1.0f;

	Light->SetIntensity(maxIntensity);

	ConstructorHelpers::FObjectFinder<USoundBase> Sound(TEXT("/Script/Engine.SoundWave'/Game/paper_pick.paper_pick'"));
	
	PaperSound = Sound.Object;

	//Fragment->AddWorldRotation(FRotator(0.0f, 90.0f, 0.0f));

	Box->OnComponentBeginOverlap.AddDynamic(this, &AFragments::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &AFragments::OnOverlapEnd);
	

}

// Called when the game starts or when spawned
void AFragments::BeginPlay()
{
	Super::BeginPlay();

	StartPulsate();
	
}

// Called every frame
void AFragments::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFragments::StartPulsate()
{
	GetWorldTimerManager().SetTimer(PulseTimer, this, &AFragments::Pulsate, 0.1f, true);
}

void AFragments::Pulsate()
{
	if (!reachedMin) {
		Light->SetIntensity(FMath::FInterpTo(Light->Intensity, minIntensity, GetWorld()->GetDeltaSeconds(), LightCSpeed * GetWorld()->GetDeltaSeconds()));
		if (Light->Intensity <= minIntensity) {
			reachedMin = true;
		}
	}
	else {
		Light->SetIntensity(FMath::FInterpTo(Light->Intensity, maxIntensity, GetWorld()->GetDeltaSeconds(), LightCSpeed * GetWorld()->GetDeltaSeconds()));
		if (Light->Intensity >= maxIntensity) {
			reachedMin = false;
		}
	}
}

void AFragments::StopPulsate()
{
	GetWorldTimerManager().ClearTimer(PulseTimer);
}

void AFragments::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProtPlayer* PlayR = Cast<AProtPlayer>(OtherActor);
	if (PlayR != nullptr) {
		HUDWidget->SetVisibility(true);
		//FTimerDelegate Del;
		//Del.BindUFunction(this, FName("OrientHUDToPlayer"), PlayR);
		//GetWorldTimerManager().SetTimer(OrientHUD, Del, 0.7f, true);
	}
}

void AFragments::OrientHUDToPlayer(AProtPlayer* Ref)
{
	HUDWidget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(HUDWidget->GetComponentLocation(), Ref->GetActorLocation()));
}

void AFragments::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtPlayer* PlayR = Cast<AProtPlayer>(OtherActor);
	if (PlayR != nullptr) {
		HUDWidget->SetVisibility(false);
		//GetWorldTimerManager().ClearTimer(OrientHUD);
	}
}

