// Fill out your copyright notice in the Description page of Project Settings.


#include "Diary.h"
#include "Components/TextRenderComponent.h"
#include "Components/SkeletalMeshComponent.h"

ADiary::ADiary()
{
	Text2 = CreateDefaultSubobject<UTextRenderComponent>("Text2");
	Text2->SetupAttachment(RootComponent);
}
