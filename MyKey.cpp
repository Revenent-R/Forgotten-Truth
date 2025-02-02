// Fill out your copyright notice in the Description page of Project Settings.


#include "MyKey.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyKey::AMyKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(KeyMesh);
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(KeyMesh);

}

// Called when the game starts or when spawned
void AMyKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

