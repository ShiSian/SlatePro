// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiGameOptionWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/SlAiStyle.h"
#include "Data/SlAiDataHandle.h"
#include "Widgets/Images/SImage.h"
#include "BPLibrary/MyBPLibrary.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameOptionWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	//【给代理绑定事件】
	ChangeCulture = InArgs._ChangeCulture;
	ChangeVolume = InArgs._ChangeVolume;


	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(300.f)
		[
			//SBox->SOverlay
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//SBox->SOverlay->SImage
			[
				SNew(SImage)
				.Image(&MenuStyle->GameOptionBGBrush)
			]
			//SBox->SOverlay->SVerticalBox
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(50.f))
			[
				//SBox->SOverlay->SVerticalBox->SHorizontalBox【第一行】
				//【新建SVerticalBox】
				SNew(SVerticalBox)
				//【给VerticalBox添加插槽】
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				//【设置插槽的填充方式】
				.FillHeight(1.f)
				[
					//SBox->SOverlay->SVerticalBox->SHorizontalBox->SCheckBox
					//【新建SHorizontalBox】
					SNew(SHorizontalBox)
					//【为HorizontalBox添加插槽】
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					//【设置插槽控件的填充方式】
					.FillWidth(1.f)
					[
						//【新建CheckBox，并赋值给变量ZhCheckBox】
						SAssignNew(ZhCheckBox, SCheckBox)
						//【设置CheckBox勾选状态改变时的事件】
						.OnCheckStateChanged(this, &SSlAiGameOptionWidget::ZhCheckBoxStateChanged)
						//【设置CheckBox的插槽】
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							//【设置TextBlock的颜色和透明度】
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SlAiMenu", "Chinese", "Chinese"))
						]
					]
					//SBox->SOverlay->SVerticalBox->SHorizontalBox->SCheckBox
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.f)
					[
						SAssignNew(EnCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SSlAiGameOptionWidget::EnCheckBoxStateChanged)
						//SBox->SOverlay->SVerticalBox->SHorizontalBox->SCheckBox->STextBlock
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SlAiMenu", "Engilish", "English"))
						]
					]
				]


				//SBox->SOverlay->SVerticalBox->SHorizontalBox【第二行】
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SOverlay)
					//第二行的左侧文字
					+SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("SlAiMenu", "Music", "Music"))
					]
					//第二行的滑动条
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						//放滑动条的SizeBox
						SNew(SBox)
						.WidthOverride(240.f)
						[
							//放Slider的Overlay
							SNew(SOverlay)
							//Slider的背景
							+SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBrush)
							]
							//添加Slider
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								//【新建Slider，并赋值给变量MuSlider】
								SAssignNew(MuSlider, SSlider)
								//【设置Slider的显示样式】
								.Style(&MenuStyle->SliderStyle)
								//【设置Slider的值发生改变时的回调事件】
								.OnValueChanged(this, &SSlAiGameOptionWidget::MusicSliderChanged)
							]
						]
					]
					//第二行的右侧文字
					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(MuTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
				//第二行结束


				//SBox->SOverlay->SVerticalBox->SHorizontalBox【第三行】
				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SOverlay)
					//第三行的左侧文字
					+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("SlAiMenu", "Sound", "Sound"))
					]
					//第三行的滑动条
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						//放滑动条的SizeBox
						SNew(SBox)
						.WidthOverride(240.f)
						[
							//放Slider的Overlay
							SNew(SOverlay)
							//Slider的背景
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBrush)
							]
							//添加Slider
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								SAssignNew(SoSlider, SSlider)
								.Style(&MenuStyle->SliderStyle)
								.OnValueChanged(this, &SSlAiGameOptionWidget::SoundSliderChanged)
							]
						]
					]
					//第三行的右侧文字
					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(SoTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
				//第三行结束


			]
		]
	];
	StyleInitialize();
}
void SSlAiGameOptionWidget::StyleInitialize()
{
	//【设置CheckBox的显示样式】
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UncheckedBoxBrush);
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UncheckedBoxBrush);
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UncheckedBoxBrush);
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	//set EnCheckBox Style
	EnCheckBox->SetUncheckedImage(&MenuStyle->UncheckedBoxBrush);
	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UncheckedBoxBrush);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UncheckedBoxBrush);
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
		ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		break;
	case ECultureTeam::CH:
		EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
		break;
	}

	MuSlider->SetValue(SlAiDataHandle::Get()->MusicVolume);
	SoSlider->SetValue(SlAiDataHandle::Get()->SoundVolume);

	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(SlAiDataHandle::Get()->MusicVolume * 100)) + FString("%")));
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(SlAiDataHandle::Get()->SoundVolume * 100)) + FString("%")));

}
void SSlAiGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState)
{
	//Set Checked CheckBox
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	//【在这里执行代理】
	ChangeCulture.ExecuteIfBound(ECultureTeam::CH);

	UMyBPLibrary::ReadJson(FString(TEXT("123")));

}
void SSlAiGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	//Set Checked CheckBox
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	//【在这里执行代理】
	ChangeCulture.ExecuteIfBound(ECultureTeam::EN);
}
void SSlAiGameOptionWidget::MusicSliderChanged(float Value)
{
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	ChangeVolume.ExecuteIfBound(Value, -1.f);
}
void SSlAiGameOptionWidget::SoundSliderChanged(float Value)
{
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	ChangeVolume.ExecuteIfBound(-1.f, Value);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
