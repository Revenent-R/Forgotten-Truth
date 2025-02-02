// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APills::APills()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Pills = CreateDefaultSubobject<UStaticMeshComponent>("Pills");
	SetRootComponent(Pills);

	HealingPower = 0.08f;
}

// Called when the game starts or when spawned
void APills::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APills::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

