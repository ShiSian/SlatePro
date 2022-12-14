// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data/SlAiTypes.h"
#include "SlAiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DIDISLATE_API ASlAiPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASlAiPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;


protected:
	virtual void BeginPlay() override;


private:
	//切换视角
	void ChangeView();
	//鼠标按键事件
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();



public:
	//获取玩家角色
	class ASlAiPlayerCharacter* SPCharacter;	


private:
	//左键预设动作
	EUpperBody::Type LeftUpperType;
	//右键预设动作
	EUpperBody::Type RightUpperType;
};
