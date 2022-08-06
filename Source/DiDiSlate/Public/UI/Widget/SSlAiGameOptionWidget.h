// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SCheckBox.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "Widgets/Input/SSlider.h"
#include "Data/SlAiTypes.h"


//�������½�����
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)

/**
 * 
 */
class DIDISLATE_API SSlAiGameOptionWidget : public SCompoundWidget
{
public:

	//��������ӵ�FArguments�еı������¼���
	// ����ı�����������Construct������FArguments������ʹ��
	// ���½��ؼ���ʱ����Զ����ﶨ��ı�����������
	// �����Ķ��������SLATE_BEGIN_ARGS��SLATE_END_ARGS֮��
	SLATE_BEGIN_ARGS(SSlAiGameOptionWidget)
	{}
	//�����¼�
	SLATE_EVENT(FChangeCulture, ChangeCulture)
	SLATE_EVENT(FChangeVolume, ChangeVolume)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//����������������
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
