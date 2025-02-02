// Fill out your copyright notice in the Description page of Project Settings.


#include "Battery.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABattery::ABattery()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BatteryMesh = CreateDefaultSubobject<UStaticMeshComponent>("Battery");
	SetRootComponent(BatteryMesh);

	Power = 0.3f;

}

// Called when the game starts or when spawned
void ABattery::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

