// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SlAiMenuHUD.h"
#include "SlateBasics.h"

ASlAiMenuHUD::ASlAiMenuHUD()
{
	//��GEngine->GameViewport��������Ϸ�ӿڡ�
	//��ΪGEngine��GameViewport������Ϊ NULL���������㳢�Է������ǻ������κγ�Աʱ������Ӧ���ж����ǵ�ֵ��
	if (GEngine && GEngine->GameViewport)
	{
		//����һ��SSlAiMenuHUDWidget�ؼ��������丳ֵ��MenuHUDWidget
		SAssignNew(MenuHUDWidget, SSlAiMenuHUDWidget);
		//�����ӿ�����ӿؼ���
			//����ӷ�ʽһ��SNew(SWeakWidget).PossiblyNullContent(Slate�ؼ�������ָ��.ToSharedRef())
			//����ӷ�ʽ����Slate�ؼ�������ָ��ToSharedRef()
		GEngine->GameViewport->AddViewportWidgetContent(MenuHUDWidget.ToSharedRef());
	}

}