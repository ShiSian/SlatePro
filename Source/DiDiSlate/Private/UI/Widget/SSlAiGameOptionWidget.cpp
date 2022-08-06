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
	//����������¼���
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
				//SBox->SOverlay->SVerticalBox->SHorizontalBox����һ�С�
				//���½�SVerticalBox��
				SNew(SVerticalBox)
				//����VerticalBox��Ӳ�ۡ�
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				//�����ò�۵���䷽ʽ��
				.FillHeight(1.f)
				[
					//SBox->SOverlay->SVerticalBox->SHorizontalBox->SCheckBox
					//���½�SHorizontalBox��
					SNew(SHorizontalBox)
					//��ΪHorizontalBox��Ӳ�ۡ�
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					//�����ò�ۿؼ�����䷽ʽ��
					.FillWidth(1.f)
					[
						//���½�CheckBox������ֵ������ZhCheckBox��
						SAssignNew(ZhCheckBox, SCheckBox)
						//������CheckBox��ѡ״̬�ı�ʱ���¼���
						.OnCheckStateChanged(this, &SSlAiGameOptionWidget::ZhCheckBoxStateChanged)
						//������CheckBox�Ĳ�ۡ�
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							//������TextBlock����ɫ��͸���ȡ�
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


				//SBox->SOverlay->SVerticalBox->SHorizontalBox���ڶ��С�
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SOverlay)
					//�ڶ��е��������
					+SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("SlAiMenu", "Music", "Music"))
					]
					//�ڶ��еĻ�����
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						//�Ż�������SizeBox
						SNew(SBox)
						.WidthOverride(240.f)
						[
							//��Slider��Overlay
							SNew(SOverlay)
							//Slider�ı���
							+SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBrush)
							]
							//���Slider
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								//���½�Slider������ֵ������MuSlider��
								SAssignNew(MuSlider, SSlider)
								//������Slider����ʾ��ʽ��
								.Style(&MenuStyle->SliderStyle)
								//������Slider��ֵ�����ı�ʱ�Ļص��¼���
								.OnValueChanged(this, &SSlAiGameOptionWidget::MusicSliderChanged)
							]
						]
					]
					//�ڶ��е��Ҳ�����
					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(MuTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
				//�ڶ��н���


				//SBox->SOverlay->SVerticalBox->SHorizontalBox�������С�
				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SOverlay)
					//�����е��������
					+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("SlAiMenu", "Sound", "Sound"))
					]
					//�����еĻ�����
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						//�Ż�������SizeBox
						SNew(SBox)
						.WidthOverride(240.f)
						[
							//��Slider��Overlay
							SNew(SOverlay)
							//Slider�ı���
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBrush)
							]
							//���Slider
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
					//�����е��Ҳ�����
					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(SoTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
				//�����н���


			]
		]
	];
	StyleInitialize();
}
void SSlAiGameOptionWidget::StyleInitialize()
{
	//������CheckBox����ʾ��ʽ��
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
	//��������ִ�д���
	ChangeCulture.ExecuteIfBound(ECultureTeam::CH);

	UMyBPLibrary::ReadJson(FString(TEXT("123")));

}
void SSlAiGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	//Set Checked CheckBox
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	//��������ִ�д���
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
