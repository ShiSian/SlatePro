// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "SlAiMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct DIDISLATE_API FSlAiMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiMenuStyle();
	virtual ~FSlAiMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiMenuStyle& GetDefault();

	/*��ҳ�汳��ͼƬ*/
	UPROPERTY(EditAnywhere, Category = "MenuHUD")
		FSlateBrush MenuHUDBackgroundBrush;

	/*��ҳ��Menu�ı���ͼƬ*/
	UPROPERTY(EditAnywhere, Category = "Menu")
		FSlateBrush MenuBackgroundBrush;

	/*Menu��ͼ���Brush*/
	UPROPERTY(EditAnywhere, Category = "Menu")
		FSlateBrush LeftIconBrush;
	/*Menu��ͼ���Brush*/
	UPROPERTY(EditAnywhere, Category = "Menu")
		FSlateBrush RightIconBrush;
	/*Menu��ͼ���Brush*/
	UPROPERTY(EditAnywhere, Category = "Menu")
		FSlateBrush TitleBorderBrush;
	/*Menu��ͼ���Brush*/
	UPROPERTY(EditAnywhere, Category = "Menu")
		FSlateFontInfo TitleFontInfo;

	/*MenuItem��Brush*/
	UPROPERTY(EditAnywhere, Category = "MenuItem")
		FSlateBrush MenuItemBrush;
	/*60������*/
	UPROPERTY(EditAnywhere, Category = "Common")
		FSlateFontInfo Font_60;
	/*40������*/
	UPROPERTY(EditAnywhere, Category = "Common")
		FSlateFontInfo Font_40;
	/*30������*/
	UPROPERTY(EditAnywhere, Category = "Common")
		FSlateFontInfo Font_30;

	/*Black Font Color*/
	UPROPERTY(EditAnywhere, Category = "Common")
		FLinearColor FontColor_Black;
	/*White Font Color*/
	UPROPERTY(EditAnywhere, Category = "Common")
		FLinearColor FontColor_White;

	/*Game set Background*/
	UPROPERTY(EditAnywhere, Category = "GameOption")
		FSlateBrush GameOptionBGBrush;
	/*CheckBox Selected Brush*/
	UPROPERTY(EditAnywhere, Category = "GameOption")
		FSlateBrush CheckedBoxBrush;
	/*CheckBox Selected Brush*/
	UPROPERTY(EditAnywhere, Category = "GameOption")
		FSlateBrush UncheckedBoxBrush;


	UPROPERTY(EditAnywhere, Category = "GameOption")
		FSlateBrush SliderBrush;
	UPROPERTY(EditAnywhere, Category = GameSet)
		FSliderStyle SliderStyle;

	/*��ʼ��Ϸ����*/
	UPROPERTY(EditAnywhere, Category = "Sound")
		FSlateSound StartGameSound;
	/*������Ϸ����*/
	UPROPERTY(EditAnywhere, Category = "Sound")
		FSlateSound ExitGameSound;
	/*ת����ť����*/
	UPROPERTY(EditAnywhere, Category = "Sound")
		FSlateSound MenuItemChangeSound;
	/* Menu�������� */
	UPROPERTY(EditAnywhere, Category = "Sound")
		FSlateSound MenuBackgroundMusic;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
