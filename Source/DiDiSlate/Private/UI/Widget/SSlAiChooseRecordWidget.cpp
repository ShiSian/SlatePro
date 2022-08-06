// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiChooseRecordWidget.h"
#include "SlateOptMacros.h"
#include "Data/SlAiDataHandle.h"
#include "UI/Style/SlAiStyle.h"
#include "Widgets/Images/SImage.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiChooseRecordWidget::Construct(const FArguments& InArgs)
{
	//获取MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	//初始化下拉菜单数据
	for (TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList); It; ++It)
	{
		OptionSource.Add(MakeShareable(new FString(*It)));
	}


	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(20.f, 0.f, 0.f, 0.f))
			[
				SNew(STextBlock)
				.Font(MenuStyle->Font_40)
				.Text(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"))
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 0.f, 20.f, 0.f))
			[
				SNew(SBox)
				.WidthOverride(300.f)
				.HeightOverride(60.f)
				[
					SAssignNew(RecordComboBox, STextComboBox)
					.Font(MenuStyle->Font_30)
					.OptionsSource(&OptionSource)
				]
			]
		]
	];
	
	//设置默认的选项
	RecordComboBox->SetSelectedItem(OptionSource[0]);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiChooseRecordWidget::UpdateRecordName()
{

}
