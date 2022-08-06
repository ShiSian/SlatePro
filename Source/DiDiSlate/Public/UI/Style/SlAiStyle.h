// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

/**
 * 
 */
class DIDISLATE_API SlAiStyle
{
public:
	static void Initialize();
	static FName GetStyleSetName();
	static void ShutDown();
	static const ISlateStyle& Get();

private:
	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> SlAiStyleInstance;
};
