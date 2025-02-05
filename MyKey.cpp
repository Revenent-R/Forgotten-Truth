// Fill out your copyright notice in the Description page of Project Settings.


#include "MyKey.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProtPlayer.h"

// Sets default values
AMyKey::AMyKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(KeyMesh);
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(KeyMesh);
	HUDWidget = CreateDefaultSubobject<UWidgetComponent>("HUD");
	HUDWidget->SetupAttachment(KeyMesh);

	HUDWidget->SetDrawSize(FVector2D(140.0f, 100.0f));
	HUDWidget->SetVisibility(false);
	HUDWidget->SetWidgetSpace(EWidgetSpace::Screen);

	Box->SetWorldScale3D(FVector(4.75f, 5.5f, 5.75f));


}

// Called when the game starts or when spawned
void AMyKey::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AMyKey::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &AMyKey::OnOverlapEnd);
	
}

// Called every frame
void AMyKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyKey::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProtPlayer* PlayR = Cast<AProtPlayer>(OtherActor);
	if (PlayR != nullptr) {
		HUDWidget->SetVisibility(true);
		//FTimerDelegate Del;
		//Del.BindUFunction(this, FName("OrientHUDToPlayer"), PlayR);
		//GetWorldTimerManager().SetTimer(OrientHUD, Del, 0.7f, true);
	}
}

void AMyKey::OrientHUDToPlayer(AProtPlayer* Ref)
{
	HUDWidget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(HUDWidget->GetComponentLocation(), Ref->GetActorLocation()));
}

void AMyKey::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProtPlayer* PlayR = Cast<AProtPlayer>(OtherActor);
	if (PlayR != nullptr) {
		HUDWidget->SetVisibility(false);
		//GetWorldTimerManager().ClearTimer(OrientHUD);
	}
}

