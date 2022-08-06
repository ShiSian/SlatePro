// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<class T>
class DIDISLATE_API SlAiSingleton
{
public:
	static TSharedPtr<T> Get();

private:
	static void Initialize();

	static TSharedRef<T> Create();

private:
	static TSharedPtr<T> TInstacne;

};

template<class T>
TSharedPtr<T> SlAiSingleton<T>::TInstacne = NULL;

template<class T>
inline TSharedPtr<T> SlAiSingleton<T>::Get()
{
	Initialize();
	return TInstacne;
}

template<class T>
inline void SlAiSingleton<T>::Initialize()
{
	if (!TInstacne.IsValid())
	{
		TInstacne = Create();
	}
}

template<class T>
inline TSharedRef<T> SlAiSingleton<T>::Create()
{
	TSharedRef<T> TRef = MakeShareable(new T());
	return TRef;
}