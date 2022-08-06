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
	//获取角色指针
	void InitSPCharacter();
	//更新属性
	virtual void UpdateParameter();
	//更新动作
	virtual void UpdateMontage();
	//修改是否允许切换视角
	void AllowViewChange(bool IsAllow);


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayAnim")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayAnim")
		FRotator SpineRotator;

protected:
	//角色指针
	class ASlAiPlayerCharacter* SPCharacter;
	//上半身的Montage
	UAnimMontage* PlayerHitMontage;
	UAnimMontage* PlayerFightMontage;
	UAnimMontage* PlayerPunchMontage;
	UAnimMontage* PlayerEatMontage;
	UAnimMontage* PlayerPickUpMontage;
	//保存当前播放的Montage
	UAnimMontage* CurrentMontage;
	//指定自己的运行人称
	EGameViewMode::Type GameView;
};
