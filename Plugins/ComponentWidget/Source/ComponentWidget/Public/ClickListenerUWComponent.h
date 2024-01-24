// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ComponentUserWidget.h"
#include "ClickListenerUWComponent.generated.h"


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