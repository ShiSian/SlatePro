// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DIDISLATE_API UMyBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "MyBPLibrary")
		static void ReadJson(const FString& JsonString);
		

	
};
