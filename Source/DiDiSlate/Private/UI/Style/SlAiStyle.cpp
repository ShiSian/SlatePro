// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/SlAiStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"


TSharedPtr<FSlateStyleSet> SlAiStyle::SlAiStyleInstance = NULL;

void SlAiStyle::Initialize()
{
	if (!SlAiStyleInstance.IsValid())
	{
		SlAiStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*SlAiStyleInstance);
	}
}

FName SlAiStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SlAiStyle"));
	return StyleSetName;
}

void SlAiStyle::ShutDown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*SlAiStyleInstance);
	ensure(SlAiStyleInstance.IsUnique());
	SlAiStyleInstance.Reset();
}

const ISlateStyle& SlAiStyle::Get()
{
	if (!SlAiStyleInstance)
	{
		Initialize();
	}
	return *SlAiStyleInstance;
}

TSharedRef<FSlateStyleSet> SlAiStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(SlAiStyle::GetStyleSetName(), 
		"/Game/UI/Style", 
		"/Game/UI/Style");
	StyleRef->Set("MenuItemFont", FSlateFontInfo("Roboto.ttf", 50));
	return StyleRef;
}
