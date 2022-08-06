// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DIDISLATE_API SlAiInternation
{
public:
	static void Register(FText Value)
	{
		return;
	}
};

#define LOCTEXT_NAMESPACE "SlAiMenu"

SlAiInternation::Register(LOCTEXT("Menu", "Menu"));

SlAiInternation::Register(LOCTEXT("StartGame", "StartGame"));
SlAiInternation::Register(LOCTEXT("GameOption", "GameOption"));
SlAiInternation::Register(LOCTEXT("QuitGame", "QuitGame"));
SlAiInternation::Register(LOCTEXT("NewGame", "NewGame"));

SlAiInternation::Register(LOCTEXT("LoadRecord", "LoadRecord"));
SlAiInternation::Register(LOCTEXT("ChooseRecord", "ChooseRecord"));
SlAiInternation::Register(LOCTEXT("RecordName", "RecordName"));
SlAiInternation::Register(LOCTEXT("EnterGame", "EnterGame"));
SlAiInternation::Register(LOCTEXT("EnterRecord", "EnterRecord"));
SlAiInternation::Register(LOCTEXT("RecordNameHint", "RecordNameHint"));
SlAiInternation::Register(LOCTEXT("NameRepeatedHint", "NameRepeatedHint"));

SlAiInternation::Register(LOCTEXT("Chinese", "Chinese"));
SlAiInternation::Register(LOCTEXT("English", "English"));
SlAiInternation::Register(LOCTEXT("Music", "Music"));
SlAiInternation::Register(LOCTEXT("Sound", "Sound"));
SlAiInternation::Register(LOCTEXT("GoBack", "GoBack"));

#undef LOCTEXT_NAMESPACE

//µÈ¼ÛÓÚ
//SlAiInternation::Register(NSLOCTEXT("SlAiMenu", "Menu", "Menu"));
