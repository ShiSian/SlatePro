// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/SlAiTypes.h"
#include "SlAiPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class DIDISLATE_API USlAiPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	USlAiPlayerAnim();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:
	//��ȡ��ɫָ��
	void InitSPCharacter();
	//��������
	virtual void UpdateParameter();
	//���¶���
	virtual void UpdateMontage();
	//�޸��Ƿ������л��ӽ�
	void AllowViewChange(bool IsAllow);


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayAnim")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayAnim")
		FRotator SpineRotator;

protected:
	//��ɫָ��
	class ASlAiPlayerCharacter* SPCharacter;
	//�ϰ����Montage
	UAnimMontage* PlayerHitMontage;
	UAnimMontage* PlayerFightMontage;
	UAnimMontage* PlayerPunchMontage;
	UAnimMontage* PlayerEatMontage;
	UAnimMontage* PlayerPickUpMontage;
	//���浱ǰ���ŵ�Montage
	UAnimMontage* CurrentMontage;
	//ָ���Լ��������˳�
	EGameViewMode::Type GameView;
};
