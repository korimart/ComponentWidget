// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ComponentUserWidget.h"
#include "Components/TextBlock.h"
#include "TextUWComponent.generated.h"


UCLASS()
class COMPONENTWIDGET_API UTextUWComponent : public UUserWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override
	{
		if (IsValid(Widget) && bShouldSetDefaultText)
		{
			SetText(DefaultText);
		}
	}

	void Init(UTextBlock* InWidget)
	{
		Widget = InWidget;
	}

	FText GetText() const
	{
		return Widget->GetText();
	}

	FString GetString() const
	{
		return GetText().ToString();
	}

	void SetText(const FText& Text)
	{
		bShouldSetDefaultText = false;
		Widget->SetText(Text);
	}

	void SetString(const FString& String)
	{
		SetText(FText::FromString(String));
	}

	void Reset()
	{
		SetText(DefaultText);
	}

private:
	UPROPERTY(EditAnywhere)
	FText DefaultText;

	UPROPERTY(Transient)
	UTextBlock* Widget;

	bool bShouldSetDefaultText = true;
};
