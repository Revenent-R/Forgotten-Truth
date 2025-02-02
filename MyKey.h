// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyKey.generated.h"

UCLASS()
class FORGOTTENTRUTH_API AMyKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyKey();
	UPROPERTY(EditDefaultsOnly,Category="Mesh")
	class UStaticMeshComponent* KeyMesh;
	UPROPERTY(EditDefaultsOnly,Category="Box")
	class UBoxComponent* Box;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
