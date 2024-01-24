// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickListenerUWComponent.h"
#include "CollapserUWComponent.h"
#include "ComponentUserWidget.h"
#include "TextUWComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
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


/**
 *
 */
UCLASS()
class UDismissableNotice : public UComponentUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	UTextUWComponent* TextComponent;
	
	UPROPERTY(VisibleAnywhere)
	UClickListenerUWComponent* ClickListener;
	
	UPROPERTY(VisibleAnywhere)
	UCollapserUWComponent* Collapser;
	
	UDismissableNotice()
	{
		TextComponent = CreateDefaultSubobject<UTextUWComponent>(TEXT("TextComponent"));
		ClickListener = CreateDefaultSubobject<UClickListenerUWComponent>(TEXT("ClickListener"));
		Collapser = CreateDefaultSubobject<UCollapserUWComponent>(TEXT("Collapser"));
	}

	// UComponentUserWidget
	virtual void InitializeComponent() override
	{
		TextComponent->Init(Text);
		Collapser->Init(SizeBox, true);

		ClickListener->OnClicked.AddWeakLambda(this, [this]()
		{
			Collapser->Collapse();
		});
	}
	// ~UComponentUserWidget

private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text;
	
	UPROPERTY(meta=(BindWidget))
	USizeBox* SizeBox;
};


/**
 *
 */
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

		ResetButton->ClickListener->OnClicked.AddWeakLambda(this, [this]()
		{
			WidgetTree->ForEachWidget([](UWidget* Each)
			{
				if (auto AsComponentUserWidget = Cast<UComponentUserWidget>(Each))
				{
					if (auto Collapser = AsComponentUserWidget->FindComponentByClass<UCollapserUWComponent>())
					{
						Collapser->Expand();
					}
				}
			});
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
	
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* NoticePanel;
	
	UPROPERTY(meta=(BindWidget))
	USimpleButton* ResetButton;
};