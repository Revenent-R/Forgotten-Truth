// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoors.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProtPlayer.h"

// Sets default values
AInteractableDoors::AInteractableDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	SetRootComponent(Door);

	ConstructorHelpers::FObjectFinder<USoundBase>Sound(TEXT("/Script/Engine.SoundWave'/Game/door_closing.door_closing'"));
	ConstructorHelpers::FObjectFinder<USoundBase>OSound(TEXT("/Script/Engine.SoundWave'/Game/Door_Opening.Door_Opening'"));

	CloseSound = Sound.Object;
	OpenSound = OSound.Object;

	DoorOpenSpeed = 1000.0f;
	isOpen = false;
	isLocked = false;

}

// Called when the game starts or when spawned
void AInteractableDoors::BeginPlay()
{
	Super::BeginPlay();

	OGRotation = GetActorRotation();
	
}

// Called every frame
void AInteractableDoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableDoors::ChangeDoorState()
{
	if (isLocked) {
		GetWorldTimerManager().ClearTimer(Ref->InteractTimer);
	}
	else {
		if (!isOpen) {
			SetActorRotation(FMath::RInterpTo(GetActorRotation(), FRotator(GetActorRotation().Pitch, OGRotation.Yaw - 90, GetActorRotation().Roll), GetWorld()->GetDeltaSeconds(), DoorOpenSpeed * GetWorld()->GetDeltaSeconds()));
			if (!isPlaying) {
				UGameplayStatics::PlaySound2D(GetWorld(), OpenSound, 1.0f, 1.0f, 1.0f, nullptr, this);
				isPlaying = true;
			}
			if (GetActorRotation().Equals(FRotator(GetActorRotation().Pitch, OGRotation.Yaw - 90, GetActorRotation().Roll), 1.0f)) {
				GetWorldTimerManager().ClearTimer(Ref->InteractTimer);
				isOpen = true;
				isPlaying = false;
			}
		}
		else {
			SetActorRotation(FMath::RInterpTo(GetActorRotation(), OGRotation, GetWorld()->GetDeltaSeconds(), DoorOpenSpeed * GetWorld()->GetDeltaSeconds()));
			if (!isPlaying) {
				UGameplayStatics::PlaySound2D(GetWorld(), CloseSound, 1.0f, 1.0f, 0.0f, nullptr, this);
				isPlaying = true;
			}
			if (GetActorRotation().Equals(OGRotation, 1.0f)) {
				GetWorldTimerManager().ClearTimer(Ref->InteractTimer);
				isOpen = false;
				isPlaying = false;
			}
		}
	}
}

