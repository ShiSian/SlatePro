// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiThirdPlayerAnim.h"
#include "Player/SlAiPlayerAnim.h"
#include "Player/SlAiPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USlAiThirdPlayerAnim::USlAiThirdPlayerAnim()
{
	//����Դ��Montage
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

	//������ֵ
	Direction = 0.f;
	//���Ƿ��ڿ��и�ֵ
	IsInAir = false;

	//�����Լ��������˳��ǵ����˳�
	GameView = EGameViewMode::Third;
}

void USlAiThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();
	//��������ھ�ֱ�ӷ��أ������ָ������ж�
	if(!SPCharacter) return;
	//��ȡ�Ƿ�����Ծ
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();
	//�ٶȳ����Yaw��ת��ȥActor������ʵ��������������Yaw��ת�õ�����Եķ���
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw - SPCharacter->GetActorRotation().Yaw;
	//��������벻���׿���ȥ����˼·����һЩ
	if (PreDir > 180.f) PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;
	Direction = PreDir;
}
