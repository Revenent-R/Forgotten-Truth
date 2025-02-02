// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDrawer.h"
#include "Components/StaticMeshComponent.h"
#include "ProtPlayer.h"

// Sets default values
AInteractableDrawer::AInteractableDrawer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Drawer = CreateDefaultSubobject<UStaticMeshComponent>("Drawer");
	SetRootComponent(Drawer);

	DrawerOpenSpeed = 50.0f;

	isOpen = false;
	MoveRange = 40.0f;

}

// Called when the game starts or when spawned
void AInteractableDrawer::BeginPlay()
{
	Super::BeginPlay();
	
	OGLocation = GetActorLocation();
	
}

// Called every frame
void AInteractableDrawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableDrawer::ChangeDrawerState()
{
	if (!isOpen) {
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), OGLocation + (GetActorForwardVector() * MoveRange), GetWorld()->GetDeltaSeconds(), DrawerOpenSpeed));
		if (FVector::Dist2D(GetActorLocation(), OGLocation + (GetActorForwardVector() * MoveRange)) <= 1.0f) {
			GetWorldTimerManager().ClearTimer(Ref->InteractDrTimer);
			isOpen = true;
		}
	}
	else {
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), OGLocation, GetWorld()->GetDeltaSeconds(), DrawerOpenSpeed));
		if (FVector::Dist2D(GetActorLocation(), OGLocation) <= 1.0f) {
			GetWorldTimerManager().ClearTimer(Ref->InteractDrTimer);
			isOpen = false;
		}
	}
}

