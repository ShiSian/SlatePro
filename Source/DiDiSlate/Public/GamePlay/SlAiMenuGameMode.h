// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlAiMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DIDISLATE_API ASlAiMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASlAiMenuGameMode();

protected:
	void BeginPlay() override;
};
