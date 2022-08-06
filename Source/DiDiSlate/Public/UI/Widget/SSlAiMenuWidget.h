// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "UI/Style/SlAiStyle.h"
#include "Data/SlAiTypes.h"
#include "SSlAiGameOptionWidget.h"
#include "SSlAiNewGameWidget.h"
#include "SSlAiChooseRecordWidget.h"

struct MenuGroup
{
	//�˵�����
	FText MenuName;
	//�˵��߶�
	float MenuHeight;
	//�������
	TArray<TSharedPtr<SCompoundWidget>> ChildWidget;
	//���캯��

	MenuGroup(const FText Name, const float	Height, TArray<TSharedPtr<SCompoundWidget>>* Children)
	{
		MenuName = Name;
		MenuHeight = Height;

		for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(*Children); It; ++It)
		{
			ChildWidget.Add(*It);
		}
	}
};

/**
 * 
 */
class DIDISLATE_API SSlAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	//�󶨵�����MenuItem�ķ���
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	//�޸�����
	void ChangeCulture(ECultureTeam Culture);
	//�޸�����
	void ChangeVolume(const float MusicVolume, const float SoundVolume);
	//��ʼ�����еĿؼ�
	void InitializedMenuList();
	//ѡ����ʾ�Ľ���
	void ChooseWidget(EMenuType::Type WidgetType);
	//�޸Ĳ˵��Ĵ�С
	void ResetWidgetSize(float NewWidth, float NewHeight);
	//��ʼ���������
	void InitializedAnimation();
	//���Źرն���
	void PlayClose(EMenuType::Type NewMenu);
	// Quit Game
	void QuitGame();
	// Enter Game
	void EnterGame();


private:
	//����ĸ��ڵ�
	TSharedPtr<SBox> RootSizeBox;
	//��ȡ��MenuStyle
	const FSlAiMenuStyle* MenuStyle;
	//�������
	TSharedPtr<STextBlock> TitleText;
	//�������洹ֱ�б�
	TSharedPtr<SVerticalBox> ContentBox;
	//����˵���
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;
	//��Ϸ����Widget��ָ��
	TSharedPtr<SSlAiGameOptionWidget> GameOptionWidget;
	//����Ϸ�ؼ�ָ��
	TSharedPtr<SSlAiNewGameWidget> NewGameWidget;
	//ѡ��浵�ؼ�ָ��
	TSharedPtr<SSlAiChooseRecordWidget> ChooseRecordWidget;
	
	
	//����������
	FCurveSequence MenuAnimation;
	//���߿�����
	FCurveHandle MenuCurve;
	//���������µĸ߶�
	float CurrentHeight;
	//�Ƿ��Ѿ���ʾMenu���
	bool IsMenuShow;
	//�Ƿ���ס��ť
	bool ControlLocked;
	//���浱ǰ�Ķ���״̬
	EMenuAnim::Type AnimState;
	//���浱ǰ�Ĳ˵�
	EMenuType::Type CurrentMenu;
};
