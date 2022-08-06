// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiMenuController.generated.h"

/**
 * 
 */
UCLASS()
class DIDISLATE_API ASlAiMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	ASlAiMenuController();

public:
	virtual void BeginPlay() override;
	
};
