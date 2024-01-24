// Copyright Epic Games, Inc. All Rights Reserved.


#include "ComponentUserWidget.h"

void UComponentUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeComponent();

	ForEachComponent([&](UUserWidgetComponent* Each) { Each->NativeOnInitialized(); });
}

void UComponentUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!IsDesignTime())
	{
		ForEachComponent([&](UUserWidgetComponent* Each) { Each->NativePreConstruct(); });
	}
}

FReply UComponentUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ForEachComponent([&](UUserWidgetComponent* Each) { Each->NativeOnMouseButtonDown(InGeometry, InMouseEvent); });

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UComponentUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ForEachComponent([&](UUserWidgetComponent* Each) { Each->NativeOnMouseButtonUp(InGeometry, InMouseEvent); });

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UComponentUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ForEachComponent([&](UUserWidgetComponent* Each) { Each->NativeTick(MyGeometry, InDeltaTime); });
}
