// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SampleWidgets.generated.h"

/**
 * 
 */
// UCLASS()
// class USimpleButton : public UKmUserWidget
// {
// 	GENERATED_BODY()
//
// public:
// 	UPROPERTY(VisibleAnywhere)
// 	UKmClickListener* ClickListener; 
// 	
// 	USimpleButton()
// 	{
// 		ClickListener = CreateDefaultSubobject<UKmClickListener>(TEXT("ClickListener"));
// 	}
// };
//
//
// /**
//  *
//  */
// UCLASS()
// class USimpleButtonWithText : public UKmUserWidget
// {
// 	GENERATED_BODY()
//
// public:
// 	UPROPERTY(VisibleAnywhere)
// 	UKmClickListener* ClickListener;
// 	
// 	UPROPERTY(VisibleAnywhere)
// 	UKmTextContainer* TextContainer;
// 	
// 	USimpleButtonWithText()
// 	{
// 		ClickListener = CreateDefaultSubobject<UKmClickListener>(TEXT("ClickListener"));
// 		TextContainer = CreateDefaultSubobject<UKmTextContainer>(TEXT("TextContainer"));
// 	}
//
// 	// UKmUserWidget
// 	virtual void InitializeComponent() override
// 	{
// 		TextContainer->Init(Text);
// 	}
// 	// ~UKmUserWidget
//
// private:
// 	UPROPERTY(meta=(BindWidget))
// 	UTextBlock* Text;
// };
//
//
// /**
//  *
//  */
// UCLASS()
// class UFoldableButton : public UKmUserWidget
// {
// 	GENERATED_BODY()
//
// public:
// 	UPROPERTY(VisibleAnywhere)
// 	UKmClickListener* ClickListener;
// 	
// 	UPROPERTY(VisibleAnywhere)
// 	UKmAnimatedCollapser* Collapser;
// 	
// 	UFoldableButton()
// 	{
// 		ClickListener = CreateDefaultSubobject<UKmClickListener>(TEXT("ClickListener"));
// 		Collapser = CreateDefaultSubobject<UKmAnimatedCollapser>(TEXT("Collapser"));
// 	}
// 	
// 	// UKmUserWidget
// 	virtual void InitializeComponent() override
// 	{
// 		Collapser->Init(SizeBox, bHorizontal);
// 	}
// 	// ~UKmUserWidget
//
// private:
// 	UPROPERTY(meta=(BindWidget))
// 	USizeBox* SizeBox;
// 	
// 	UPROPERTY(EditAnywhere)
// 	bool bHorizontal = false;
// };
//
//
UCLASS()
class UMainWidget : public UUserWidget
{
	GENERATED_BODY()
};