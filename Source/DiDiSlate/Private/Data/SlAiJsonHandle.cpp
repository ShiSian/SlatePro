// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SlAiJsonHandle.h"
#include <DiDiSlate/Public/Common/SlAiHelper.h>

SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	RelativePath = FString("Res/ConfigData/");
}

bool SlAiJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		FString AbsPath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsPath))
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsPath))
			{
				return true;
			}
			else
			{
				SlAiHelper::Debug(FString("Load Error") + AbsPath);
			}
		}
		else
		{
			SlAiHelper::Debug(FString("File Not Exist") + AbsPath);
		}
	}
	return false;
}

bool SlAiJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid() && JsonObj->Values.Num() > 0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), JsonWriter);
		return true;
	}
	return false;
}

bool SlAiJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (!JsonStr.IsEmpty())
	{
		if (!FileName.IsEmpty())
		{
			FString AbsoPath = FPaths::ProjectContentDir() + RelativePath + FileName;
			//保存
			if (FFileHelper::SaveStringToFile(JsonStr, *AbsoPath))
			{
				return true;
			}
			else
			{
				SlAiHelper::Debug(FString("Save") + AbsoPath + FString("-->Failed"), 10.f);
			}
		}
	}
	return false;
}

bool SlAiJsonHandle::MyTestReadFile()
{
	//FString filePath = FPaths::GameContentDir() + TEXT("MysqlConfig/Connect.json");
	//if (FPaths::FileExists(filePath))
	//{
	//	FString server;
	//	FString dbName;
	//	FString userId;
	//	FString passwd;
	//	TArray<FName> connectConfig;
	//	FString fileStr;
	//	FFileHelper::LoadFileToString(fileStr, *filePath);
	//	TSharedPtr<FJsonObject> rootObject = MakeShareable(new FJsonObject());
	//	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(fileStr);
	//	if (FJsonSerializer::Deserialize(jsonReader, rootObject))
	//	{
	//		server = rootObject->GetStringField("server");
	//		dbName = rootObject->GetStringField("dbName");
	//		userId = rootObject->GetStringField("userId");
	//		passwd = rootObject->GetStringField("passwd");
	//	}
	//	connectConfig.Add(FName(*server));
	//	connectConfig.Add(FName(*dbName));
	//	connectConfig.Add(FName(*userId));
	//	connectConfig.Add(FName(*passwd));
	//}

	//return TArray<FName>();

	return false;
}

void SlAiJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		//获取数据
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));
		//获取存档数据
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));
		for (int i = 0; i < RecordDataArray.Num(); i++)
		{
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			RecordDataList.Add(RecordDataName);
		}
	}
	else
	{
		SlAiHelper::Debug(FString("Deserizlize Failed"));
	}
}

void SlAiJsonHandle::UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray< TSharedPtr<FJsonValue>> BaseDataArray;

	TSharedPtr<FJsonObject> CultureObject = MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture", Culture);
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObject));

	TSharedPtr<FJsonObject> MusicVolumeObject = MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume", MusicVolume);
	TSharedPtr<FJsonValueObject> MusicVolumeValue = MakeShareable(new FJsonValueObject(MusicVolumeObject));

	TSharedPtr<FJsonObject> SoundVolumeObject = MakeShareable(new FJsonObject);
	SoundVolumeObject->SetNumberField("SoundVolume", SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue = MakeShareable(new FJsonValueObject(SoundVolumeObject));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;
	for (int i = 0; i < RecordDataList->Num(); ++i)
	{
		TSharedPtr<FJsonObject> RecordItem = MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i), (*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordItem));
		RecordDataArray.Add(RecordDataValue);
	}

	TSharedPtr<FJsonObject> RecorddataObject = MakeShareable(new FJsonObject);
	RecorddataObject->SetArrayField("RecordData", RecordDataArray);
	TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecorddataObject));

	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);

	JsonObject->SetArrayField("T", BaseDataArray);

	FString JsonStr;
	GetFStringInJsonData(JsonObject, JsonStr);
	SlAiHelper::Debug(FString("Origin Str : " + JsonStr), 60.f);

	//去掉多余字符串
	JsonStr.RemoveAt(0, 8);
	JsonStr.RemoveFromEnd(FString("}"));
	SlAiHelper::Debug(FString("Final Str : " + JsonStr), 60.f);

	//写入文件
	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);

}
