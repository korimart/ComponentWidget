// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "Blueprint/UserWidget.h"
#include "ComponentUserWidget.generated.h"


/**
 * UUserWidget에서도 Composition을 사용하기 위한 클래스
 * @see UComponentUserWidget
 */
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


/**
 * AActor에서 UActorComponent를 사용해서 Composition을 구현한 것처럼 UUserWidget에서도 Composition을 구현합니다.
 * Composition을 하기 위해서는 UUserWidget 대신 이 클래스를 상속하고 UUserWidgetComponent를 상속하는
 * 컴포넌트 클래스를 Default Subobject로 생성하여 멤버 UPROPERTY로 저장합니다.
 *
 * 컴포넌트에 따라 사용 전 초기화가 필요한 경우에는 AActor와 마찬가지로 UComponentUserWidget::InitializeComponent에서
 * 초기화할 수 있습니다. 
 */
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
