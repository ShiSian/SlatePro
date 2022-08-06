// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuItemWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuItemWidget::Construct(const FArguments& InArgs)
{

	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	//【可以在InArgs参数中获取之前定义的属性和事件】
	//给代理实例绑定事件
	OnClicked = InArgs._OnClicked;
	ItemType = InArgs._ItemType.Get();
	
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
				.ColorAndOpacity(this, &SSlAiMenuItemWidget::GetTintColor)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(InArgs._ItemText)
				.Font(MenuStyle->Font_60)
			]
		]
	];
	IsMouseButtonDown = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


FReply SSlAiMenuItemWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = true;
	return FReply::Handled();
}
FReply SSlAiMenuItemWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (IsMouseButtonDown)
	{
		IsMouseButtonDown = false;
		OnClicked.ExecuteIfBound(ItemType);
	}
	return FReply::Handled();
}
void SSlAiMenuItemWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = false;
}


FSlateColor SSlAiMenuItemWidget::GetTintColor() const
{
	if (IsMouseButtonDown)  return FLinearColor(1.f, 1.f, 1.f, 0.5f);
	return FLinearColor(1.f, 1.f, 1.f, 1.f);
}
