// Fill out your copyright notice in the Description page of Project Settings.


#include "Battery.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProtPlayer.h"

// Sets default values
ABattery::ABattery()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BatteryMesh = CreateDefaultSubobject<UStaticMeshComponent>("Battery");
	SetRootComponent(BatteryMesh);
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxTrigger->SetupAttachment(BatteryMesh);
	HUDWidget = CreateDefaultSubobject<UWidgetComponent>("HUD");
	HUDWidget->SetupAttachment(BatteryMesh);

	HUDWidget->SetDrawSize(FVector2D(140.0f, 100.0f));

	HUDWidget->SetVisibility(false);
	HUDWidget->SetWidgetSpace(EWidgetSpace::Screen);

	BoxTrigger->SetWorldScale3D(FVector(4.75f, 5.5f, 5.75f));

	Power = 0.3f;

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABattery::OnOverlapBegin);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ABattery::OnOverlapEnd);

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

void ABattery::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProtPlayer* PlayR = Cast<AProtPlayer>(OtherActor);
	if (PlayR != nullptr) {
		HUDWidget->SetVisibility(true);
		//FTimerDelegate Del;
		//Del.BindUFunction(this, FName("OrientHUDToPlayer"), PlayR);
		//GetWorldTimerManager().SetTimer(OrientHUD, Del, 0.7f, true);
	}
}

void ABattery::OrientHUDToPlayer(AProtPlayer* Ref)
{
	HUDWidget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(HUDWidget->GetComponentLocation(), Ref->GetActorLocation()));
}

void ABattery::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtPlayer* PlayR = Cast<AProtPlayer>(OtherActor);
	if (PlayR != nullptr) {
		HUDWidget->SetVisibility(false);
		//GetWorldTimerManager().ClearTimer(OrientHUD);
	}
}

