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
	//����
	ECultureTeam CurrentCulture;
	//����
	float MusicVolume;
	float SoundVolume;
	//�浵����
	TArray<FString> RecordDataList;
	//�浵��
	FString RecordName;


private:
	//��������
	static TSharedRef<SlAiDataHandle> Create();
	//����ö�����ͻ�ȡ�ַ���
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);
	//�����ַ�����ȡö��ֵ
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, const FString& Value);
	//��ʼ���浵����
	void InitRecordData();
	//��ʼ��Menu��������
	void InitializedMenuAudio();


private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
	//����Menu������
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;
	//��ȡ��MenuStyle
	const FSlAiMenuStyle* MenuStyle;




	
};
