// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickListenerUWComponent.h"
#include "CollapserUWComponent.h"
#include "ComponentUserWidget.h"
#include "TextUWComponent.h"
#include "Blueprint/UserWidget.h"
#include "SampleWidgets.generated.h"

/**
 * 
 */
UCLASS()
class USimpleButton : public UComponentUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	UTextUWComponent* TextComponent;
	
	UPROPERTY(VisibleAnywhere)
	UClickListenerUWComponent* ClickListener;
	
	USimpleButton()
	{
		TextComponent = CreateDefaultSubobject<UTextUWComponent>(TEXT("TextComponent"));
		ClickListener = CreateDefaultSubobject<UClickListenerUWComponent>(TEXT("ClickListener"));
	}

	// UComponentUserWidget
	virtual void InitializeComponent() override
	{
		TextComponent->Init(Text);
	}
	// ~UComponentUserWidget

private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text;
};


/**
 * 
 */
UCLASS()
class USimpleFoldable : public UComponentUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	UCollapserUWComponent* Collapser; 
	
	USimpleFoldable()
	{
		Collapser = CreateDefaultSubobject<UCollapserUWComponent>(TEXT("Collapser"));
	}

	// UComponentUserWidget
	virtual void InitializeComponent() override
	{
		Collapser->Init(SizeBox);
	}
	// ~UComponentUserWidget

private:
	UPROPERTY(meta=(BindWidget))
	USizeBox* SizeBox;
};


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


UCLASS()
class UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// UUserWidget
	virtual void NativeOnInitialized() override
	{
		Super::NativeOnInitialized();

		ExpandLoremButton->ClickListener->OnClicked.AddWeakLambda(this, [this]()
		{
			LoremLipsum->Collapser->Expand();
		});
		
		CollapseLoremButton->ClickListener->OnClicked.AddWeakLambda(this, [this]()
		{
			LoremLipsum->Collapser->Collapse();
		});
	}
	// ~UUserWidget

private:
	UPROPERTY(meta=(BindWidget))
	USimpleFoldable* LoremLipsum;
	
	UPROPERTY(meta=(BindWidget))
	USimpleButton* ExpandLoremButton;
	
	UPROPERTY(meta=(BindWidget))
	USimpleButton* CollapseLoremButton;
};