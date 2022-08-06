﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuWidget.h"
#include "SlateOptMacros.h"
#include "Internationalization/Internationalization.h"
#include "UI/Widget/SSlAiMenuItemWidget.h"
#include "UI/Widget/SSlAiGameOptionWidget.h"
#include "Data/SlAiDataHandle.h"
#include "UI/Widget/SSlAiNewGameWidget.h"
#include "UI/Widget/SSlAiChooseRecordWidget.h"
#include "SlAiMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "Common/SlAiHelper.h"





BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuWidget::Construct(const FArguments& InArgs)
{
	//获取MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	//播放背景音乐
	FSlateApplication::Get().PlaySound(MenuStyle->MenuBackgroundMusic);


	//设置默认语言为英文
	//FInternationalization::Get().SetCurrentCulture(TEXT("en"));  

	ChildSlot
		[
			//【新建SBox控件，并赋值给变量RootSizeBox】
			SAssignNew(RootSizeBox, SBox)
			[
				SNew(SOverlay)
				+SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(FMargin(0.f, 50.f, 0.f, 0.f))
					[
						SNew(SImage)
						.Image(&MenuStyle->MenuBackgroundBrush)
					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
					[
						SNew(SImage)
						.Image(&MenuStyle->LeftIconBrush)
					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
					[
						SNew(SImage)
						.Image(&MenuStyle->RightIconBrush)
					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Top)
					[
						SNew(SBox)
						.WidthOverride(400.f)
						.HeightOverride(100.f)
						[
							//【新建SBorder控件】
							SNew(SBorder)
							//【设置Border控件的背景Image】
							.BorderImage(&MenuStyle->TitleBorderBrush)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							[
								//【在这里添加Border控件的子控件】
								//【添加STextBlock控件，并赋值为TitleText】
								SAssignNew(TitleText, STextBlock)
								//【设置TextBlock的字体】
								.Font(MenuStyle->Font_60)
								//【设置TextBlock的Text】
								//NSLOCTEXT（本地化文字所在的命名空间，本地化文字，本地化文字）
								//关于语言本地话的介绍参见其他章节
								.Text(NSLOCTEXT("SlAiMenu", "Menu", "Menu"))
							]
						]
					] 
				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Top)
					.Padding(FMargin(0.f, 130.f, 0.f, 0.f))
					[
						//【新建SVerticalBox，并赋值给ContentBox变量】
						SAssignNew(ContentBox, SVerticalBox)
						/*等价于ContentBox->AssSlot()[SNew(SSlAiGameOptionWidget)]*/
						//【给VerticalBox添加一个插槽】
						//+SVerticalBox::Slot()
						//[
						//	//【在这里为插槽添加子控件】
						//	SNew(SSlAiGameOptionWidget)
						//	.ChangeCulture(this, &SSlAiMenuWidget::ChangeCulture)
						//	.ChangeVolume(this, &SSlAiMenuWidget::ChangeVolume)
						//]
					]
			]
		];

	//RootSizeBox->SetWidthOverride(600.f);
	//RootSizeBox->SetHeightOverride(510.f);

	//ContentBox->AddSlot()
	//	[
	//		//【在这里为插槽添加子控件】
	//		//SNew(SSlAiGameOptionWidget)
	//		//.ChangeCulture(this, &SSlAiMenuWidget::ChangeCulture)
	//		//.ChangeVolume(this, &SSlAiMenuWidget::ChangeVolume)

	//		SNew(SSlAiChooseRecordWidget)
	//	];


	InitializedMenuList();
	InitializedAnimation();
}

void SSlAiMenuWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	switch (AnimState)
	{
	case EMenuAnim::Stop:
		break;
	case EMenuAnim::Close:
		//如果正在播放
		if (MenuAnimation.IsPlaying())
		{
			//实时修改Menu的大小
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, -1.f);
			//在关闭了40%的时候设置不显示组件
			if (MenuCurve.GetLerp() < 0.6f && IsMenuShow) ChooseWidget(EMenuType::None);
		}
		else
		{
			//关闭动画完了设置状态为打开
			AnimState = EMenuAnim::Open;
			//开始播放打开动画
			MenuAnimation.Play(this->AsShared());
		}
		break;
	case EMenuAnim::Open:
		//如果正在播放
		if (MenuAnimation.IsPlaying())
		{
			//实时修改Menu的大小
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, CurrentHeight);
			//打开60%之后显示组件
			if (MenuCurve.GetLerp() > 0.6f && !IsMenuShow) ChooseWidget(CurrentMenu);
		}
		// 如果播放完毕
		if (MenuAnimation.IsAtEnd())
		{
			//修改状态为Stop
			AnimState = EMenuAnim::Stop;
			// 解锁按钮
			ControlLocked = false;
		}
		break;
	default:
		break;
	}
}

void SSlAiMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	//如果锁住了，直接return
	if (ControlLocked) return;
	// 设置锁住了按钮
	ControlLocked = true;
	switch (ItemType)
	{
	case EMenuItem::None:
		break;
	case EMenuItem::StartGame:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::GameOption:
		PlayClose(EMenuType::GameOption);
		break;
	case EMenuItem::QuitGmme:
		//quit game, play sound and call quit game function for a while.
		SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->ExitGameSound, this, &SSlAiMenuWidget::QuitGame);
		break;
	case EMenuItem::NewGame:
		PlayClose(EMenuType::NewGame);
		break;
	case EMenuItem::LoadRecord:
		PlayClose(EMenuType::ChooseRecord);
		break;
	case EMenuItem::StartGameGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::GameOptionGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::NewGameGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::ChooseRecordGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::EnterGame:
		//检测是否可以进入游戏
		if (NewGameWidget->AllowEnterGame())
		{
			SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), 
				MenuStyle->StartGameSound, this, &SSlAiMenuWidget::EnterGame);
		}
		else
		{
			//解锁按钮
			ControlLocked = false;
		}
		break;
	case EMenuItem::EnterRecord:
		//告诉选择存档更新存档名
		ChooseRecordWidget->UpdateRecordName();
		SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), 
			MenuStyle->StartGameSound, this, &SSlAiMenuWidget::EnterGame);
		break;
	}
}
void SSlAiMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	SlAiDataHandle::Get()->ChangeLocalizationCulture(Culture);
}
void SSlAiMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	SlAiDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiMenuWidget::InitializedMenuList()
{
	//实例化主界面
	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "StartGame", "StartGame"))
		.ItemType(EMenuItem::StartGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GameOption", "GameOption"))
		.ItemType(EMenuItem::GameOption).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "QuitGame", "QuitGame"))
		.ItemType(EMenuItem::QuitGmme).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::MainMenu, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "Menu", "Menu"), 510.f, &MainMenuList)));

	//开始游戏界面
	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"))
		.ItemType(EMenuItem::NewGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "LoadRecord", "LoadRecord"))
		.ItemType(EMenuItem::LoadRecord).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack"))
		.ItemType(EMenuItem::StartGameGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::StartGame, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "StartGame", "StartGame"), 510.f, &StartGameList)));

	//游戏设置界面
	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
	//实例化游戏设置的Widget
	SAssignNew(GameOptionWidget, SSlAiGameOptionWidget)
		.ChangeCulture(this, &SSlAiMenuWidget::ChangeCulture)
		.ChangeVolume(this, &SSlAiMenuWidget::ChangeVolume);
	GameOptionList.Add(GameOptionWidget);  //添加控件到数组	
	GameOptionList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack"))
		.ItemType(EMenuItem::GameOptionGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::GameOption, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "GameOption", "GameOption"), 610.f, &GameOptionList)));

	//开始新游戏界面
	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
	SAssignNew(NewGameWidget, SSlAiNewGameWidget);
	NewGameList.Add(NewGameWidget);  //添加控件到数组	
	NewGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "EnterGame", "EnterGame"))
		.ItemType(EMenuItem::EnterGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	NewGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack"))
		.ItemType(EMenuItem::NewGameGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::NewGame, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"), 510.f, &NewGameList)));

	//选择存档界面
	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
	SAssignNew(ChooseRecordWidget, SSlAiChooseRecordWidget);
	ChooseRecordList.Add(ChooseRecordWidget);  //添加控件到数组	
	ChooseRecordList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "EnterRecord", "EnterRecord"))
		.ItemType(EMenuItem::EnterGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	ChooseRecordList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack"))
		.ItemType(EMenuItem::ChooseRecordGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::ChooseRecord, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "LoadRecord", "LoadRecord"), 510.f, &ChooseRecordList)));
}

void SSlAiMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	//定义是否已经显示菜单
	IsMenuShow = WidgetType != EMenuType::None;
	//移除所有组件
	ContentBox->ClearChildren(); 
	//如果MenuType是None就返回
	if (WidgetType == EMenuType::None) return;
	//循环添加组件
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; ++It)
	{
		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];
	}
	//更改标题
	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);
}

void SSlAiMenuWidget::ResetWidgetSize(float NewWidth, float NewHeight)
{
	RootSizeBox->SetWidthOverride(NewWidth);
	if (NewHeight < 0) return;
	RootSizeBox->SetHeightOverride(NewHeight);
}

void SSlAiMenuWidget::InitializedAnimation()
{
	//开始延时
	const float StartDelay = 0.3f;

	//持续时间
	const float AnimDuration = 0.6f;
	MenuAnimation = FCurveSequence();
	MenuCurve = MenuAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);
	//初始设置Menu的大小
	ResetWidgetSize(600.f, 510.f);
	//初始显示主界面
	ChooseWidget(EMenuType::MainMenu);
	//允许点击按钮
	ControlLocked = false;
	//设置动画状态为停止
	AnimState = EMenuAnim::Stop;
	//设置动画播放器跳到结尾也就是1
	MenuAnimation.JumpToEnd();
}

void SSlAiMenuWidget::PlayClose(EMenuType::Type NewMenu)
{
	//设置新的界面
	CurrentMenu = NewMenu;
	//设置新高度
	CurrentHeight = (*MenuMap.Find(NewMenu))->MenuHeight;
	//设置播放状态是Close
	AnimState = EMenuAnim::Close;
	//播放反向动画
	MenuAnimation.PlayReverse(this->AsShared());
	//播放切换菜单音乐
	FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound);
}

void SSlAiMenuWidget::QuitGame()
{
	Cast<ASlAiMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
}

void SSlAiMenuWidget::EnterGame()
{
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("GameMap"));
}
