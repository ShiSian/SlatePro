// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SlAiDataHandle.h"
#include "Data/SlAiJsonHandle.h"
#include "Common/SlAiHelper.h"
#include "Data/SlAiSingleton.h"
#include "UI/Style/SlAiStyle.h"

TSharedPtr<SlAiDataHandle> SlAiDataHandle::DataInstance = NULL;

SlAiDataHandle::SlAiDataHandle()
{
	//初始化存档数据
	InitRecordData();
	//初始化音乐数据
	InitializedMenuAudio();
}

void SlAiDataHandle::Initialize()
{
	if (!DataInstance.IsValid())
	{
		DataInstance = Create();
	}
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Get()
{
	Initialize();
	return DataInstance;
}


TSharedRef<SlAiDataHandle> SlAiDataHandle::Create()
{
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle);
	return DataRef;
}

void SlAiDataHandle::InitRecordData()
{
	FString Culture;
	SlAiSingleton<SlAiJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);

	RecordName = FString("");

	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));

	SlAiHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) + FString("--") + FString::SanitizeFloat(SoundVolume), 20.f);

	for (TArray<FString>::TIterator It(RecordDataList); It; ++It)
	{
		SlAiHelper::Debug(*It, 20.f);
	}
}

void SlAiDataHandle::InitializedMenuAudio()
{
	//获取MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");

	//添加资源文件到资源列表
	TArray<USoundCue*> MusicList;
	MusicList.Add(Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject()));
	TArray<USoundCue*> SoundList;
	SoundList.Add(Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->ExitGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->MenuItemChangeSound.GetResourceObject()));

	//添加资源到Map
	MenuAudioResource.Add(FString("Music"), MusicList);
	MenuAudioResource.Add(FString("Sound"), SoundList);
	
	//重置一下声音
	ResetMenuVolume(MusicVolume, SoundVolume);
}

void SlAiDataHandle::ChangeLocalizationCulture(ECultureTeam Culture)
{
	switch (Culture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ECultureTeam::CH:
		FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
		break;
	}

	CurrentCulture = Culture;
	//更新存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"),
		CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

void SlAiDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;
		//循环设置背景音量
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator()); It; ++It)
		{
			(*It)->VolumeMultiplier = MusicVolume;
		}
	}

	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;
		//循环设置背景音量
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator()); It; ++It)
		{
			(*It)->VolumeMultiplier = SoundVolume;
		}
	}
	//更新存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(
		GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"),CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

template<typename TEnum>
FString SlAiDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return FString("InValid");
	}
	return EnumPtr->GetNameStringByValue((int32)Value);
	//return EnumPtr->GetEnumName((int32)Value);
}

template<typename TEnum>
TEnum SlAiDataHandle::GetEnumValueFromString(const FString& Name, const FString& Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}