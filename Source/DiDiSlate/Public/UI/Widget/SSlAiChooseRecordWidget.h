// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/STextComboBox.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"



/**
 * 
 */
class DIDISLATE_API SSlAiChooseRecordWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiChooseRecordWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	//���´浵��
	void UpdateRecordName();

private:
	//��ȡMenuStyle
	const struct FSlAiMenuStyle* MenuStyle;
	//�����˵�
	TSharedPtr<STextComboBox> RecordComboBox;
	//�ַ�ָ������
	TArray<TSharedPtr<FString>> OptionSource;
};