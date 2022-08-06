// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "Widgets/SOverlay.h"
#include "SSlAiMenuWidget.h"

/**
 * 
 */
class DIDISLATE_API SSlAiMenuHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//��UIScaler�ĺ���
	float GetUIScaler() const;
	//��ȡ��Ļ�ߴ�
	FVector2D GetViewportSize() const;



private:
	//��ȡMenu��ʽ
	const struct FSlAiMenuStyle* MenuStyle;
	//DPI����ϵ��
	TAttribute<float> UIScaler;
	//�˵�ָ��
	TSharedPtr<SSlAiMenuWidget> MenuWidget;
};


