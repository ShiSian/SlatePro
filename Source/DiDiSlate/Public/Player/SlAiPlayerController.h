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
	//�л��ӽ�
	void ChangeView();
	//��갴���¼�
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();



public:
	//��ȡ��ҽ�ɫ
	class ASlAiPlayerCharacter* SPCharacter;	


private:
	//���Ԥ�趯��
	EUpperBody::Type LeftUpperType;
	//�Ҽ�Ԥ�趯��
	EUpperBody::Type RightUpperType;
};
