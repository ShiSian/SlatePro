// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "UI/Style/SlAiStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SDPIScaler.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuHUDWidget::Construct(const FArguments& InArgs)
{
	//获取蓝图中设置的MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	
	//绑定缩放规则方法
	UIScaler.Bind(this, &SSlAiMenuHUDWidget::GetUIScaler);
	
	ChildSlot
	[
		SNew(SDPIScaler)
		.DPIScale(UIScaler)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&MenuStyle->MenuHUDBackgroundBrush)
				]
			//+SOverlay::Slot()
			//	.HAlign(HAlign_Center)
			//	.VAlign(VAlign_Center) 
			//	[
			//		SNew(SImage)
			//		.Image(&MenuStyle->MenuBackgroundBrush)
			//	]
			+SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SAssignNew(MenuWidget, SSlAiMenuWidget)
				]
		]
	];
}


float SSlAiMenuHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080;
}
FVector2D SSlAiMenuHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920, 1080);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}


	return Result;
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
