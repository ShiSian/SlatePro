// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SlAiMenuHUD.h"
#include "SlateBasics.h"

ASlAiMenuHUD::ASlAiMenuHUD()
{
	//【GEngine->GameViewport：访问游戏视口】
	//因为GEngine和GameViewport都可以为 NULL，所以在你尝试访问它们或者其任何成员时，总是应该判断它们的值。
	if (GEngine && GEngine->GameViewport)
	{
		//创建一个SSlAiMenuHUDWidget控件，并将其赋值给MenuHUDWidget
		SAssignNew(MenuHUDWidget, SSlAiMenuHUDWidget);
		//【向视口中添加控件】
			//【添加方式一】SNew(SWeakWidget).PossiblyNullContent(Slate控件的智能指针.ToSharedRef())
			//【添加方式二】Slate控件的智能指针ToSharedRef()
		GEngine->GameViewport->AddViewportWidgetContent(MenuHUDWidget.ToSharedRef());
	}

}