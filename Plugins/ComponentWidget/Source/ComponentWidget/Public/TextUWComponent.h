// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ComponentUserWidget.h"
#include "Components/TextBlock.h"
#include "TextUWComponent.generated.h"


/**
 * UTextBlock 한 개를 컴포넌트화 한 클래스
 * 
 * UTextBlock의 FText에 대한 여러가지 편의함수를 제공하고 에디터 블루프린트에서 기본 텍스트를 설정할 수 있게 합니다.
 * @see UTextUWComponent::DefaultText
 * 
 * 사용 전 반드시 UTextUWComponent::Init을 호출해야 합니다.
 */
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
