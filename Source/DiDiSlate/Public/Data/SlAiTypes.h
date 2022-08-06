// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ECultureTeam : uint8
{
	EN = 0,
	CH = 1
};

//Menu��ť������
namespace EMenuItem
{
	enum Type
	{
		None,
		StartGame,
		GameOption,
		QuitGmme,
		NewGame,
		LoadRecord,
		StartGameGoBack,
		GameOptionGoBack,
		NewGameGoBack,
		ChooseRecordGoBack,
		EnterGame,
		EnterRecord
	};
}

namespace EMenuType
{
	enum Type
	{
		None,
		MainMenu,
		StartGame,
		GameOption,
		NewGame,
		ChooseRecord
	};
}

namespace EMenuAnim
{
	enum Type
	{
		Stop, //ֹͣ����
		Close, //�ر�Menu
		Open //��Menu
	};
}

//�ӽ�ģʽ
namespace EGameViewMode
{
	enum Type
	{
		First,
		Third
	};
}

//�ϰ�������״̬
namespace EUpperBody
{
	enum Type
	{
		None,
		Punch,
		Hit,
		Fight,
		PickUp,
		Eat
	};
}