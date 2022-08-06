// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DIDISLATE_API SlAiJsonHandle
{
public:
	SlAiJsonHandle();

public:
	//�����浵����
	void RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList);
	//�޸Ĵ浵
	void UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList);

private:
	//��ȡJson�ļ����ַ���
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

	//FJSONObjectת��ΪJson��ʽ���ַ���
	bool GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr);

	//�����ַ������ļ�
	bool WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName);

	bool MyTestReadFile();
	



private:
	//�浵�ļ���
	FString RecordDataFileName;


	//���·��
	FString RelativePath;
};
