// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDoors.generated.h"

UCLASS()
class FORGOTTENTRUTH_API AInteractableDoors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableDoors();
	UPROPERTY(EditDefaultsOnly,Category="Door")
	class UStaticMeshComponent* Door;
	UPROPERTY(EditDefaultsOnly,Category="Box")
	class UBoxComponent* BoxT;
	UPROPERTY(EditDefaultsOnly,Category="UI")
	class UWidgetComponent* HUDWidget;
	UPROPERTY(EditDefaultsOnly,Category="Sound")
	class USoundBase* CloseSound;
	UPROPERTY(EditDefaultsOnly,Category="Sound")
	class USoundBase* OpenSound;

	bool isPlaying;
	bool isOpen;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Lock")
	bool isLocked;

	FRotator OGRotation;

	class AProtPlayer* Ref;

	float DoorOpenSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeDoorState();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void FindPositionForHUD(class AProtPlayer* FHUDRef);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
