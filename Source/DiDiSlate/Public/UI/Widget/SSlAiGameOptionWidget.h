// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SCheckBox.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "Widgets/Input/SSlider.h"
#include "Data/SlAiTypes.h"


//在这里新建代理
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)

/**
 * 
 */
class DIDISLATE_API SSlAiGameOptionWidget : public SCompoundWidget
{
public:

	//【定义添加到FArguments中的变量和事件】
	// 定义的变量将可以在Construct函数的FArguments参数中使用
	// 在新建控件的时候可以对这里定义的变量进行设置
	// 变量的定义必须在SLATE_BEGIN_ARGS和SLATE_END_ARGS之间
	SLATE_BEGIN_ARGS(SSlAiGameOptionWidget)
	{}
	//定义事件
	SLATE_EVENT(FChangeCulture, ChangeCulture)
	SLATE_EVENT(FChangeVolume, ChangeVolume)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//【在这里声明代理】
	FChangeCulture ChangeCulture;
	FChangeVolume ChangeVolume;

	/*Get MenuStylel*/
	const FSlAiMenuStyle* MenuStyle;
	/*Get CheckBox  pointer*/
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;
	/*Get Slider pointer*/
	TSharedPtr<SSlider> MuSlider;
	TSharedPtr<SSlider> SoSlider;
	/*Slider Percent Text*/
	TSharedPtr<STextBlock> MuTextBlock;
	TSharedPtr<STextBlock> SoTextBlock;


private:
	// Set CheckBox Style
	void StyleInitialize();
	//When ZhCheckBox State Change
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	//When EnCheckBox State Change
	void EnCheckBoxStateChanged(ECheckBoxState NewState);
	//When Slider Change
	void MusicSliderChanged(float Value);
	void SoundSliderChanged(float Value);

};
