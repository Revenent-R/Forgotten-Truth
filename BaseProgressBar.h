// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class FORGOTTENTRUTH_API UBaseProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly,meta=(BindWidget))
	class UPanelWidget* RootPanel;

	UPROPERTY(EditAnywhere,meta = (BindWidget))
	class UProgressBar* ProgressBar;
	
	void SetProgress(float Curr, float Max);

	void SetColorOnEmpty(FLinearColor NewColor);
	
};
