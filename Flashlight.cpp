// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashlight.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "ProtPlayer.h"

// Sets default values
AFlashlight::AFlashlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FlashLight = CreateDefaultSubobject<UStaticMeshComponent>("FlashLight");
	SetRootComponent(FlashLight);
	Light = CreateDefaultSubobject<USpotLightComponent>("SLight");
	Light->SetupAttachment(FlashLight);
	HUDWidget = CreateDefaultSubobject<UWidgetComponent>("HUD");
	HUDWidget->SetupAttachment(FlashLight);
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxT");
	BoxTrigger->SetupAttachment(FlashLight);


	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFlashlight::OnOverlapBegin);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AFlashlight::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlashlight::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProtPlayer* PlayR = Cast<AProtPlayer>(OtherActor);
	if (PlayR != nullptr) {
		HUDWidget->SetVisibility(true);
	}
}

void AFlashlight::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtPlayer* PlayR = Cast<AProtPlayer>(OtherActor);
	if (PlayR != nullptr) {
		HUDWidget->SetVisibility(false);
	}
}

