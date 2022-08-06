// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiThirdPlayerAnim.h"
#include "Player/SlAiPlayerAnim.h"
#include "Player/SlAiPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USlAiThirdPlayerAnim::USlAiThirdPlayerAnim()
{
	//绑定资源到Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerHitMontage.PlayerHitMontage'"));
	if (PlayerHitMon.Succeeded()) PlayerHitMontage = PlayerHitMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerEatMontage.PlayerEatMontage'"));
	if (PlayerEatMon.Succeeded()) PlayerEatMontage = PlayerEatMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerFightMontage.PlayerFightMontage'"));
	if (PlayerFightMon.Succeeded()) PlayerFightMontage = PlayerFightMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPunchMontage.PlayerPunchMontage'"));
	if (PlayerPunchMon.Succeeded()) PlayerPunchMontage = PlayerPunchMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPickUpMontage.PlayerPickUpMontage'"));
	if (PlayerPickUpMon.Succeeded()) PlayerPickUpMontage = PlayerPickUpMon.Object;

	//给方向赋值
	Direction = 0.f;
	//给是否在空中赋值
	IsInAir = false;

	//设置自己的运行人称是第三人称
	GameView = EGameViewMode::Third;
}

void USlAiThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();
	//如果不存在就直接返回，避免空指针产生中断
	if(!SPCharacter) return;
	//获取是否在跳跃
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();
	//速度朝向的Yaw旋转减去Actor朝向，其实就是摄像机朝向的Yaw旋转得到的相对的方向
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw - SPCharacter->GetActorRotation().Yaw;
	//如果这里想不明白可以去玩点乘思路清晰一些
	if (PreDir > 180.f) PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;
	Direction = PreDir;
}
