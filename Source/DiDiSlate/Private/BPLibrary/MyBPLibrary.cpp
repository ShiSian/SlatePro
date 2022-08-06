// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLibrary/MyBPLibrary.h"
#include "Policies/PrettyJsonPrintPolicy.h"
#include "Common/SlAiHelper.h"

void UMyBPLibrary::ReadJson(const FString& JsonString)
{
	//https://blog.csdn.net/qq_35760525/article/details/77531286

	//【创建一个JsonObject】
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	//【设置JsonObject的JsonValue】
	//布尔格式
	JsonObject->SetBoolField("BoolField", true);
	//数值格式
	JsonObject->SetNumberField("NumberField", 1);
	//字符串格式
	JsonObject->SetStringField("StringField", "TestString");
	//Json格式
	TSharedPtr<FJsonObject> TmpJsonObject = MakeShareable(new FJsonObject);
	TmpJsonObject->SetStringField("Type", "TmpJsonObject");
	JsonObject->SetObjectField("ObjectField", TmpJsonObject);
	//数组格式_布尔
	TArray<TSharedPtr<FJsonValue>> JsonValueArray_Bool;
	for (int i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonValueBoolean> TmpBoolJsonValue = MakeShareable(new FJsonValueBoolean(false));
		JsonValueArray_Bool.Add(TmpBoolJsonValue);
	}
	JsonObject->SetArrayField("ArrayField_Bool", JsonValueArray_Bool);
	//数组格式_数值
	TArray<TSharedPtr<FJsonValue>> JsonValueArray_Number;
	for (int i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonValueNumber> TmpNumberJsonValue = MakeShareable(new FJsonValueNumber(i));
		JsonValueArray_Number.Add(TmpNumberJsonValue);
	}
	JsonObject->SetArrayField("ArrayField_Number", JsonValueArray_Number);
	//数组格式_字符串
	TArray<TSharedPtr<FJsonValue>> JsonValueArray_String;
	for (int i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonValueString> TmpStringJsonValue = MakeShareable(new FJsonValueString(FString::FromInt(i)));
		JsonValueArray_String.Add(TmpStringJsonValue);
	}
	JsonObject->SetArrayField("ArrayField_String", JsonValueArray_String);
	//数组格式_Json
	TArray<TSharedPtr<FJsonValue>> JsonValueArray_Json;
	for (int i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonObject> TmpInsideJsonObject = MakeShareable(new FJsonObject);
		TmpInsideJsonObject->SetNumberField("Number", i);
		TSharedPtr<FJsonValueObject> TmpJsonObject1 = MakeShareable(new FJsonValueObject(TmpInsideJsonObject));
		JsonValueArray_Json.Add(TmpJsonObject1);
	}
	JsonObject->SetArrayField("ArrayField_Json", JsonValueArray_Json);




	//【Json转FString】
	FString OutputString1;
	FString OutputString2;
	FString OutputString3;
	if (JsonObject.IsValid() && JsonObject->Values.Num() > 0)
	{
		//FJsonObject转为字符串后存储到OutputString1中
		TSharedRef<TJsonWriter<>> JsonWriter1 = TJsonWriterFactory<>::Create(&OutputString1);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter1);
		SlAiHelper::Debug(OutputString1);
		/*【输出的结果】对字符串进行了缩进和换行
		{
			"BoolField": true,
			"NumberField": 1,
			"StringField": "TestString",
			"ObjectField":
			{
				"Type": "TmpJsonObject"
			},
			"ArrayField_Bool": [ false, false, false ],
			"ArrayField_Number": [ 0, 1, 2 ],
			"ArrayField_String": [
				"0",
				"1",
				"2"
			],
			"ArrayField_Json": [
				{
					"Number": 0
				},
				{
					"Number": 1
				},
				{
					"Number": 2
				}
			]
		}
		*/

		//FJsonObject转为字符串后存储到OutputString2中
		//TSharedRef<TJsonWriter<>> Writer2 = TJsonWriterFactory<>::Create(&OutputString2);
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter2 = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutputString2);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter2);
		SlAiHelper::Debug(OutputString2);
		/*【输出的结果】没有缩进和换行
		{"BoolField":true,"NumberField":1,"StringField":"TestString","ObjectField":{"Type":"TmpJsonObject"},"ArrayField_Bool":[false,false,false],"ArrayField_Number":[0,1,2],"ArrayField_String":["0","1","2"],"ArrayField_Json":[{"Number":0},{"Number":1},{"Number":2}]}
		*/

		//FJsonObject转为字符串后存储到OutputString3中
		//TSharedRef<TJsonWriter<>> Writer3 = TJsonWriterFactory<>::Create(&OutputString3);
		TSharedRef< TJsonWriter< TCHAR, TPrettyJsonPrintPolicy<TCHAR> > > JsonWriter3 = TJsonWriterFactory< TCHAR, TPrettyJsonPrintPolicy<TCHAR> >::Create(&OutputString3);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter3);
		SlAiHelper::Debug(OutputString3);
		/*【输出的结果同结果1】会进行缩进和换行*/
	}

	
	//【FSting转Json】
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(OutputString1);
	//OutputString1是Json格式的字符串
	TSharedPtr<FJsonObject> JsonValueReader;
	FJsonSerializer::Deserialize(JsonReader, JsonValueReader);

	//【读取-布尔格式】
	bool BoolValue;
	JsonValueReader->TryGetBoolField("BoolField", BoolValue);  //读取方式1
	BoolValue = JsonValueReader->GetBoolField("BoolField");    //读取方式2
	//【读取-数值格式】
	float NumberField;
	JsonValueReader->TryGetNumberField("NumberField", NumberField);
}
