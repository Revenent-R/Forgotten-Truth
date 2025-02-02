// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fragments.generated.h"

UCLASS()
class FORGOTTENTRUTH_API AFragments : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFragments();
	UPROPERTY(EditDefaultsOnly,Category="Fragment")
	class UStaticMeshComponent* Fragment;
	UPROPERTY(EditDefaultsOnly,Category="Box")
	class UBoxComponent* Box;
	UPROPERTY(EditDefaultsOnly,Category="Text")
	class UTextRenderComponent* Text;
	UPROPERTY(EditDefaultsOnly,Category = "Sound")
	class USoundCue* Narration;
	UPROPERTY(EditDefaultsOnly,Category="Sound")
	class USoundBase* PaperSound;
	UPROPERTY(EditDefaultsOnly,Category="Light")
	class UPointLightComponent* Light;

	FTimerHandle PulseTimer;

	UPROPERTY(EditAnywhere)
	bool Last;

	float LightCSpeed;
	float maxIntensity;
	float minIntensity;
	bool reachedMin;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartPulsate();
	void Pulsate();
	void StopPulsate();

};
