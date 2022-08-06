// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SlAiTypes.h"
#include "Sound/SoundCue.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"

/**
 * 
 */
class DIDISLATE_API SlAiDataHandle
{
public:
	SlAiDataHandle();
	static void Initialize();
	static TSharedPtr<SlAiDataHandle> Get();
	void ChangeLocalizationCulture(ECultureTeam Culture);
	void ResetMenuVolume(float MusicVol, float SoundVol);


public:
	//语言
	ECultureTeam CurrentCulture;
	//音量
	float MusicVolume;
	float SoundVolume;
	//存档数据
	TArray<FString> RecordDataList;
	//存档名
	FString RecordName;


private:
	//创建单例
	static TSharedRef<SlAiDataHandle> Create();
	//根据枚举类型获取字符串
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);
	//根据字符串获取枚举值
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, const FString& Value);
	//初始化存档数据
	void InitRecordData();
	//初始化Menu声音数据
	void InitializedMenuAudio();


private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
	//保存Menu的声音
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;
	//获取的MenuStyle
	const FSlAiMenuStyle* MenuStyle;




	
};
