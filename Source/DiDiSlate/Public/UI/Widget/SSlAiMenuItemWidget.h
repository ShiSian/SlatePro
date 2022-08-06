// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SlAiTypes.h"
#include "UI/Widget/SSlAiMenuHUDWidget.h"
#include "UI/Style/SlAiStyle.h"
#include "Widgets/SCompoundWidget.h"

//�������ﶨ�����
DECLARE_DELEGATE_OneParam(FItemClicked, EMenuItem::Type)

/**
 * 
 */
class DIDISLATE_API SSlAiMenuItemWidget : public SCompoundWidget
{
public:
	//��������ӵ�FArguments�е����Ժ��¼���
	// ����ı�����������Construct������FArguments������ʹ��
	// ���½��ؼ���ʱ����Զ����ﶨ��ı�����������
	// ���Ժ��¼��Ķ��������SLATE_BEGIN_ARGS��SLATE_END_ARGS֮��
	SLATE_BEGIN_ARGS(SSlAiMenuItemWidget)
		//����������Զ�������Խ��г�ʼ��(������ǰ��Ҫ���»��ߣ�
		:_MyVector(FVector2D(0.f)) 
	{

	}

	//��������
	//SLATE_ATTRIBUTE���������ͣ� ��������
	SLATE_ATTRIBUTE(FText, ItemText)
	SLATE_ATTRIBUTE(EMenuItem::Type, ItemType)
	SLATE_ATTRIBUTE(FVector2D, MyVector)
	//�����¼�
	//SLATE_EVENT���������ͣ�����ʵ����[ͬʱҲ���¼���]��
	SLATE_EVENT(FItemClicked, OnClicked)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


	//��д�����OnMouseButtonDown����
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//����뿪
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;



private:
	//����������
	FItemClicked OnClicked;

	//��ȡ��ɫ
	FSlateColor GetTintColor() const;
	//��ȡMenuStyle
	const FSlAiMenuStyle* MenuStyle;
	//���水ť����
	EMenuItem::Type ItemType;
	//��ť�Ƿ��Ѿ�����
	bool IsMouseButtonDown;
};
