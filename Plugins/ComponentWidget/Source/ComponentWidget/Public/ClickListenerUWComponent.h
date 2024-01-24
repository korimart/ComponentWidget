// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ComponentUserWidget.h"
#include "ClickListenerUWComponent.generated.h"


/**
 * 위젯이 클릭 입력을 받을 때 이벤트를 발생시키는 컴포넌트
 */
UCLASS()
class COMPONENTWIDGET_API UClickListenerUWComponent : public UUserWidgetComponent
{
	GENERATED_BODY()

public:
	FSimpleMulticastDelegate OnClicked;

	virtual void NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override
	{
		OnClicked.Broadcast();
	}
};