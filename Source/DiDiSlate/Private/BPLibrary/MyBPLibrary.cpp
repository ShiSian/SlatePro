// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLibrary/MyBPLibrary.h"
#include "Policies/PrettyJsonPrintPolicy.h"
#include "Common/SlAiHelper.h"

void UMyBPLibrary::ReadJson(const FString& JsonString)
{
	//https://blog.csdn.net/qq_35760525/article/details/77531286

	//������һ��JsonObject��
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	//������JsonObject��JsonValue��
	//������ʽ
	JsonObject->SetBoolField("BoolField", true);
	//��ֵ��ʽ
	JsonObject->SetNumberField("NumberField", 1);
	//�ַ�����ʽ
	JsonObject->SetStringField("StringField", "TestString");
	//Json��ʽ
	TSharedPtr<FJsonObject> TmpJsonObject = MakeShareable(new FJsonObject);
	TmpJsonObject->SetStringField("Type", "TmpJsonObject");
	JsonObject->SetObjectField("ObjectField", TmpJsonObject);
	//�����ʽ_����
	TArray<TSharedPtr<FJsonValue>> JsonValueArray_Bool;
	for (int i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonValueBoolean> TmpBoolJsonValue = MakeShareable(new FJsonValueBoolean(false));
		JsonValueArray_Bool.Add(TmpBoolJsonValue);
	}
	JsonObject->SetArrayField("ArrayField_Bool", JsonValueArray_Bool);
	//�����ʽ_��ֵ
	TArray<TSharedPtr<FJsonValue>> JsonValueArray_Number;
	for (int i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonValueNumber> TmpNumberJsonValue = MakeShareable(new FJsonValueNumber(i));
		JsonValueArray_Number.Add(TmpNumberJsonValue);
	}
	JsonObject->SetArrayField("ArrayField_Number", JsonValueArray_Number);
	//�����ʽ_�ַ���
	TArray<TSharedPtr<FJsonValue>> JsonValueArray_String;
	for (int i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonValueString> TmpStringJsonValue = MakeShareable(new FJsonValueString(FString::FromInt(i)));
		JsonValueArray_String.Add(TmpStringJsonValue);
	}
	JsonObject->SetArrayField("ArrayField_String", JsonValueArray_String);
	//�����ʽ_Json
	TArray<TSharedPtr<FJsonValue>> JsonValueArray_Json;
	for (int i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonObject> TmpInsideJsonObject = MakeShareable(new FJsonObject);
		TmpInsideJsonObject->SetNumberField("Number", i);
		TSharedPtr<FJsonValueObject> TmpJsonObject1 = MakeShareable(new FJsonValueObject(TmpInsideJsonObject));
		JsonValueArray_Json.Add(TmpJsonObject1);
	}
	JsonObject->SetArrayField("ArrayField_Json", JsonValueArray_Json);




	//��JsonתFString��
	FString OutputString1;
	FString OutputString2;
	FString OutputString3;
	if (JsonObject.IsValid() && JsonObject->Values.Num() > 0)
	{
		//FJsonObjectתΪ�ַ�����洢��OutputString1��
		TSharedRef<TJsonWriter<>> JsonWriter1 = TJsonWriterFactory<>::Create(&OutputString1);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter1);
		SlAiHelper::Debug(OutputString1);
		/*������Ľ�������ַ��������������ͻ���
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

		//FJsonObjectתΪ�ַ�����洢��OutputString2��
		//TSharedRef<TJsonWriter<>> Writer2 = TJsonWriterFactory<>::Create(&OutputString2);
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter2 = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutputString2);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter2);
		SlAiHelper::Debug(OutputString2);
		/*������Ľ����û�������ͻ���
		{"BoolField":true,"NumberField":1,"StringField":"TestString","ObjectField":{"Type":"TmpJsonObject"},"ArrayField_Bool":[false,false,false],"ArrayField_Number":[0,1,2],"ArrayField_String":["0","1","2"],"ArrayField_Json":[{"Number":0},{"Number":1},{"Number":2}]}
		*/

		//FJsonObjectתΪ�ַ�����洢��OutputString3��
		//TSharedRef<TJsonWriter<>> Writer3 = TJsonWriterFactory<>::Create(&OutputString3);
		TSharedRef< TJsonWriter< TCHAR, TPrettyJsonPrintPolicy<TCHAR> > > JsonWriter3 = TJsonWriterFactory< TCHAR, TPrettyJsonPrintPolicy<TCHAR> >::Create(&OutputString3);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter3);
		SlAiHelper::Debug(OutputString3);
		/*������Ľ��ͬ���1������������ͻ���*/
	}

	
	//��FStingתJson��
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(OutputString1);
	//OutputString1��Json��ʽ���ַ���
	TSharedPtr<FJsonObject> JsonValueReader;
	FJsonSerializer::Deserialize(JsonReader, JsonValueReader);

	//����ȡ-������ʽ��
	bool BoolValue;
	JsonValueReader->TryGetBoolField("BoolField", BoolValue);  //��ȡ��ʽ1
	BoolValue = JsonValueReader->GetBoolField("BoolField");    //��ȡ��ʽ2
	//����ȡ-��ֵ��ʽ��
	float NumberField;
	JsonValueReader->TryGetNumberField("NumberField", NumberField);
}
