// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiFirstPlayerAnim.h"

USlAiFirstPlayerAnim::USlAiFirstPlayerAnim()
{
	//绑定资源到Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerHitMontage.FirstPlayerHitMontage'"));
	if (PlayerHitMon.Succeeded()) PlayerHitMontage = PlayerHitMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerEatMontage.FirstPlayerEatMontage'"));
	if (PlayerEatMon.Succeeded()) PlayerEatMontage = PlayerEatMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerFightMontage.FirstPlayerFightMontage'"));
	if (PlayerFightMon.Succeeded()) PlayerFightMontage = PlayerFightMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerPunchMontage.FirstPlayerPunchMontage'"));
	if (PlayerPunchMon.Succeeded()) PlayerPunchMontage = PlayerPunchMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon
		(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerPickUpMontage.FirstPlayerPickUpMontage'"));
	if (PlayerPickUpMon.Succeeded()) PlayerPickUpMontage = PlayerPickUpMon.Object;

	//设置自己的运行人称是第一人称
	GameView = EGameViewMode::First;
}
