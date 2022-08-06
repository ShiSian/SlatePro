// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/SlAiGameMode.h"
#include "UI/HUD/SlAiGameHUD.h"
#include "Player/SlAiPlayerController.h"
#include "Player/SlAiPlayerState.h"
#include "Player/SlAiPlayerCharacter.h"
#include "Data/SlAiDataHandle.h"
#include "Common/SlAiHelper.h"
#include "SlAiGameInstance.h"
#include "Kismet/GameplayStatics.h"

ASlAiGameMode::ASlAiGameMode()
{
	//允许开启Tick函数
	PrimaryActorTick.bCanEverTick = true;

	//添加组件
	HUDClass = ASlAiGameHUD::StaticClass();
	PlayerControllerClass = ASlAiPlayerController::StaticClass();
	PlayerStateClass = ASlAiPlayerState::StaticClass();
	DefaultPawnClass = ASlAiPlayerCharacter::StaticClass();
}

void ASlAiGameMode::Tick(float DeltaSeconds)
{

}

void ASlAiGameMode::BeginPlay()
{
	SlAiHelper::Debug(FString("DataHandle : ") + SlAiDataHandle::Get()->RecordName, 30.f);
	SlAiHelper::Debug(FString("GameInstance : ") + Cast<USlAiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName, 30.f);
}
