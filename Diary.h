// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fragments.h"
#include "Diary.generated.h"

/**
 * 
 */
UCLASS()
class FORGOTTENTRUTH_API ADiary : public AFragments
{
	GENERATED_BODY()

public:

	ADiary();

	UPROPERTY(EditDefaultsOnly,Category="Anim")
	class UAnimationAsset* OpenBook;
	UPROPERTY(EditDefaultsOnly,Category="Anim")
	class UAnimationAsset* CloseBook;
	UPROPERTY(EditDefaultsOnly,Category="Text")
	class UTextRenderComponent* Text2;
	
};
