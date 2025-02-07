// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProtPlayer.generated.h"

UCLASS()
class FORGOTTENTRUTH_API AProtPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProtPlayer();
	UPROPERTY(EditDefaultsOnly,Category="Camera")
	class UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly,Category="Sound")
	class USoundBase* BackSound;


	bool FragmentPicked;
	float Range;
	float InterpSpeed;


	UPROPERTY(BlueprintReadOnly)
	bool mRight;
	UPROPERTY(BlueprintReadOnly)
	bool Jumping;
	UPROPERTY(BlueprintReadOnly)
	bool Sprinting;
	UPROPERTY(BlueprintReadOnly)
	float RL;


	UPROPERTY(BlueprintReadOnly)
	float Power;
	float Drain;

	bool InputEnabled;

	UPROPERTY(EditDefaultsOnly,Category="CutScene")
	class UAnimationAsset* CutScene;

	UPROPERTY(BlueprintReadOnly)
	float Paranoia;
	int32 PillsAmount;
	int32 BatteryAmount;
	float Heal;
	bool isOn;
	FTimerHandle InteractTimer;
	FTimerHandle InteractDrTimer;

	UPROPERTY(BlueprintReadOnly)
	float SprintPower;

	class AFragments* Memory;

	float Timer;
	float TimerT;
	UPROPERTY(BlueprintReadOnly)
	int32 Index;
	bool hasKey;
	UPROPERTY(BlueprintReadOnly)
	class UAudioComponent* Audio;

	UPROPERTY(EditAnywhere,Category="Flash")
	class AFlashlight* Flash;

	UPROPERTY(BlueprintReadOnly)
	bool hasFlashlight;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<class UUserWidget> MainWidgetClass;
	class UBaseHUDWidget* MainWidget;
	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<class UUserWidget> BatteryWidgetClass;
	class UBaseProgressBar* BatteryWidget;
	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<class UUserWidget> SprintWidgetClass;
	class UBaseProgressBar* SprintWidget;

	UPROPERTY(EditAnywhere)
	class ADiary* DiaryRef;

	bool hasBookOpened;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float val);
	void MoveRight(float val);
	void Turn(float val);
	void LookUp(float val);
	void Jump();
	void StopJumping();

	void IdleTimer(float DeltaTime);

	void StartFragmentPick();
	UFUNCTION()
	void FragmentPickUp(class AFragments* PickedFragment);

	void PickupPills();
	void ConsumePills();

	void PickUpFlashLight();

	void Interact();

	void StartSprint();
	void Sprint();
	void StopSprint();

	void ResetColor();

	void StartCutScene();
	void StopCutScene();

	void StartOpenBook();
	void OpenBook();

	void ChangeFlashLightState();

};
