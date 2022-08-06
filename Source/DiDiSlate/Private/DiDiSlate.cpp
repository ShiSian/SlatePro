// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiDiSlate.h"
#include "Modules/ModuleManager.h"
#include "UI/Style/SlAiStyle.h"
#include "Styling/SlateStyleRegistry.h"


void FDiDiSlateModule::StartupModule()
{
	//��ʼ����ʽ����ֹ������ģ��ע���������ظ�ע�ᣬ����������ȡ��ע��
	FSlateStyleRegistry::UnRegisterSlateStyle(SlAiStyle::GetStyleSetName());
	//��ʼ��
	SlAiStyle::Initialize();
}

void FDiDiSlateModule::ShutdownModule()
{
	SlAiStyle::ShutDown();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDiDiSlateModule, DiDiSlate, "DiDiSlate");
//IMPLEMENT_GAME_MODULE(FDiDiSlateModule, DiDiSlate/*, "DiDiSlate"*/)
