// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiDiSlate.h"
#include "Modules/ModuleManager.h"
#include "UI/Style/SlAiStyle.h"
#include "Styling/SlateStyleRegistry.h"


void FDiDiSlateModule::StartupModule()
{
	//初始化样式，防止在其他模块注册过，造成重复注册，所以这里先取消注册
	FSlateStyleRegistry::UnRegisterSlateStyle(SlAiStyle::GetStyleSetName());
	//初始化
	SlAiStyle::Initialize();
}

void FDiDiSlateModule::ShutdownModule()
{
	SlAiStyle::ShutDown();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDiDiSlateModule, DiDiSlate, "DiDiSlate");
//IMPLEMENT_GAME_MODULE(FDiDiSlateModule, DiDiSlate/*, "DiDiSlate"*/)
