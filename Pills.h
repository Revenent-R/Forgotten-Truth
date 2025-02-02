// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pills.generated.h"

UCLASS()
class FORGOTTENTRUTH_API APills : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APills();
	UPROPERTY(EditDefaultsOnly,Category="Mesh")
	class UStaticMeshComponent* Pills;
	UPROPERTY(EditDefaultsOnly,Category="Prop")
	float HealingPower;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
