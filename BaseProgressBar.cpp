// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProgressBar.h"
#include "Components/ProgressBar.h"
#include "Components/PanelWidget.h"

void UBaseProgressBar::SetProgress(float Curr, float Max)
{
	ProgressBar->SetPercent(Curr / Max);
}

void UBaseProgressBar::SetColorOnEmpty(FLinearColor NewColor)
{
	ProgressBar->SetFillColorAndOpacity(NewColor);
}
