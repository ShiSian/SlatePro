// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/SSlAiMenuHUDWidget.h"
#include "SlAiMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIDISLATE_API ASlAiMenuHUD : public AHUD
{
	GENERATED_BODY()
public:
	ASlAiMenuHUD();

	TSharedPtr<SSlAiMenuHUDWidget> MenuHUDWidget;
};
