// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "Blueprint/UserWidget.h"
#include "ComponentUserWidget.generated.h"


UCLASS(DefaultToInstanced, Within=ComponentUserWidget)
class COMPONENTWIDGET_API UUserWidgetComponent : public UObject
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() {}
	virtual void NativeOnInitialized() {}
	virtual void NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {}
	virtual void NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {}
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {}

	class UComponentUserWidget* GetOwner() const
	{
		return GetOuterUComponentUserWidget();
	}
};


UCLASS()
class COMPONENTWIDGET_API UComponentUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UComponentUserWidget()
		: Super(*FUObjectThreadContext::Get().TopInitializer())
	{
	}

	template <typename T>
	T* FindComponentByClass()
	{
		for (TFieldIterator<FObjectProperty> It(GetClass()); It; ++It)
		{
			if (It->PropertyClass == T::StaticClass())
			{
				return *It->ContainerPtrToValuePtr<T*>(this);
			}
		}
		return nullptr;
	}

	template <typename FuncType>
	void ForEachComponent(FuncType&& Func)
	{
		for (TFieldIterator<FObjectProperty> It(GetClass()); It; ++It)
		{
			if (It->PropertyClass->IsChildOf(UUserWidgetComponent::StaticClass()))
			{
				Func(*It->ContainerPtrToValuePtr<UUserWidgetComponent*>(this));
			}
		}
	}

protected:
	// UUserWidget
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	// ~UUserWidget

	virtual void InitializeComponent() {}
};
