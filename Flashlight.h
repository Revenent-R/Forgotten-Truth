// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

UCLASS()
class FORGOTTENTRUTH_API AFlashlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashlight();
	UPROPERTY(EditDefaultsOnly,Category="Mesh")
	class UStaticMeshComponent* FlashLight;
	UPROPERTY(EditDefaultsOnly,Category="Light")
	class USpotLightComponent* Light;
	UPROPERTY(EditDefaultsOnly,Category="UI")
	class UWidgetComponent* HUDWidget;
	UPROPERTY(EditDefaultsOnly,Category="Trigger")
	class UBoxComponent* BoxTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
