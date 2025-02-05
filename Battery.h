// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battery.generated.h"

UCLASS()
class FORGOTTENTRUTH_API ABattery : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattery();
	UPROPERTY(EditDefaultsOnly,Category="Mesh")
	class UStaticMeshComponent* BatteryMesh;
	UPROPERTY(EditDefaultsOnly,Category="Box")
	class UBoxComponent* BoxTrigger;
	UPROPERTY(EditDefaultsOnly,Category="UI")
	class UWidgetComponent* HUDWidget;

	float Power;
	FTimerHandle OrientHUD;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OrientHUDToPlayer(class AProtPlayer* Ref);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
