// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDrawer.generated.h"

UCLASS()
class FORGOTTENTRUTH_API AInteractableDrawer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableDrawer();
	UPROPERTY(EditDefaultsOnly,Category="Drawers")
	class UStaticMeshComponent* Drawer;

	FVector OGLocation;

	class AProtPlayer* Ref;

	bool isOpen;

	float DrawerOpenSpeed;
	float MoveRange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeDrawerState();

};
