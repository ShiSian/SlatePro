// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SlAiTypes.h"
#include "UI/Widget/SSlAiMenuHUDWidget.h"
#include "UI/Style/SlAiStyle.h"
#include "Widgets/SCompoundWidget.h"

//【在这里定义代理】
DECLARE_DELEGATE_OneParam(FItemClicked, EMenuItem::Type)

/**
 * 
 */
class DIDISLATE_API SSlAiMenuItemWidget : public SCompoundWidget
{
public:
	//【定义添加到FArguments中的属性和事件】
	// 定义的变量将可以在Construct函数的FArguments参数中使用
	// 在新建控件的时候可以对这里定义的变量进行设置
	// 属性和事件的定义必须在SLATE_BEGIN_ARGS和SLATE_END_ARGS之间
	SLATE_BEGIN_ARGS(SSlAiMenuItemWidget)
		//可以在这里对定义的属性进行初始化(变量名前需要加下划线）
		:_MyVector(FVector2D(0.f)) 
	{

	}

	//定义属性
	//SLATE_ATTRIBUTE（属性类型， 属性名）
	SLATE_ATTRIBUTE(FText, ItemText)
	SLATE_ATTRIBUTE(EMenuItem::Type, ItemType)
	SLATE_ATTRIBUTE(FVector2D, MyVector)
	//定义事件
	//SLATE_EVENT（代理类型，代理实例名[同时也是事件名]）
	SLATE_EVENT(FItemClicked, OnClicked)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


	//重写组件的OnMouseButtonDown方法
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//鼠标离开
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;



private:
	//【声明代理】
	FItemClicked OnClicked;

	//获取颜色
	FSlateColor GetTintColor() const;
	//获取MenuStyle
	const FSlAiMenuStyle* MenuStyle;
	//保存按钮类型
	EMenuItem::Type ItemType;
	//按钮是否已经按下
	bool IsMouseButtonDown;
};
