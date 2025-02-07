// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FORGOTTENTRUTH_API UBaseHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	class UCanvasPanel* Panel;
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	class UVerticalBox* VBox;
	
};
