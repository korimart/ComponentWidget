// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ComponentUserWidget.h"
#include "FloatAnimator.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "CollapserUWComponent.generated.h"


UCLASS()
class COMPONENTWIDGET_API UCollapserUWComponent : public UUserWidgetComponent
{
	GENERATED_BODY()

private:
	class ICollapserImpl
	{
	public:
		virtual ~ICollapserImpl() = default;

		virtual float GetFullSize() const = 0;
		virtual float GetCurrentSize() const = 0;
		virtual void SetSize(float Size) = 0;
		virtual void SetSizeImmediately(float Size) = 0;
	};


	class FHorizontalCollapser : public ICollapserImpl
	{
	public:
		FHorizontalCollapser(USizeBox* InSizeBox)
			: SizeBox(InSizeBox)
		{
			auto Slate = SizeBox->TakeWidget();
			SizeBox->SetClipping(EWidgetClipping::ClipToBounds);
			SizeBox->ClearWidthOverride();
		}

		virtual float GetFullSize() const override
		{
			// Collapse 되어 있는 사이에 Content 의 사이즈가 바뀌었을 수도 있음
			SizeBox->GetChildAt(0)->ForceLayoutPrepass();
			return SizeBox->GetChildAt(0)->GetDesiredSize().X;
		}

		virtual float GetCurrentSize() const override
		{
			return SizeBox->GetDesiredSize().X;
		}

		virtual void SetSize(float Size) override
		{
			SizeBox->SetWidthOverride(Size);
		}

		virtual void SetSizeImmediately(float Size) override
		{
			SetSize(Size);
			SizeBox->GetChildAt(0)->ForceLayoutPrepass();
		}

	private:
		TWeakObjectPtr<USizeBox> SizeBox;
	};


	class FVerticalCollapser : public ICollapserImpl
	{
	public:
		FVerticalCollapser(USizeBox* InSizeBox)
			: SizeBox(InSizeBox)
		{
			auto Slate = SizeBox->TakeWidget();
			SizeBox->SetClipping(EWidgetClipping::ClipToBounds);
			SizeBox->ClearHeightOverride();
		}

		virtual float GetFullSize() const override
		{
			// Collapse 되어 있는 사이에 Content 의 사이즈가 바뀌었을 수도 있음
			SizeBox->GetChildAt(0)->ForceLayoutPrepass();
			return SizeBox->GetChildAt(0)->GetDesiredSize().Y;
		}

		virtual float GetCurrentSize() const override
		{
			return SizeBox->GetDesiredSize().Y;
		}

		virtual void SetSize(float Size) override
		{
			SizeBox->SetHeightOverride(Size);
		}

		virtual void SetSizeImmediately(float Size) override
		{
			SetSize(Size);
			SizeBox->GetChildAt(0)->ForceLayoutPrepass();
		}

	private:
		TWeakObjectPtr<USizeBox> SizeBox;
	};


	class FHorizontalBoxSlotCollapser : public ICollapserImpl
	{
	public:
		FHorizontalBoxSlotCollapser(UHorizontalBoxSlot* InSlot)
			: Slot(InSlot)
		{
			ensureAlways(Slot->GetSize().SizeRule == ESlateSizeRule::Fill);
			Slot->Content->SetClipping(EWidgetClipping::ClipToBounds);
			FullSize = Slot->GetSize().Value;
		}

		virtual float GetFullSize() const override
		{
			return FullSize;
		}

		virtual float GetCurrentSize() const override
		{
			return Slot->GetSize().Value;
		}

		virtual void SetSize(float Size) override
		{
			FSlateChildSize NewSize;
			NewSize.Value = Size;
			Slot->SetSize(NewSize);
		}

		virtual void SetSizeImmediately(float Size) override
		{
			SetSize(Size);
		}

	private:
		TWeakObjectPtr<UHorizontalBoxSlot> Slot;
		float FullSize = 0.f;
	};


public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override
	{
		Animator.Tick(InDeltaTime);
	}

	void Init(USizeBox* SizeBox, bool bHorizontal = false, bool bCollapseOnInit = false)
	{
		if (bHorizontal)
		{
			CollapserImpl = MakeUnique<FHorizontalCollapser>(SizeBox);
		}
		else
		{
			CollapserImpl = MakeUnique<FVerticalCollapser>(SizeBox);
		}

		if (bCollapseOnInit)
		{
			CollapseImmediately();
		}
	}

	void Init(UHorizontalBoxSlot* Slot, bool bCollapseOnInit = false)
	{
		CollapserImpl = MakeUnique<FHorizontalBoxSlotCollapser>(Slot);

		if (bCollapseOnInit)
		{
			CollapseImmediately();
		}
	}

	void Expand()
	{
		Animator.EaseOut(CollapserImpl->GetCurrentSize(), CollapserImpl->GetFullSize(), 10.f, 2.f,
			FFloatAnimator::FOnValueChanged::CreateWeakLambda(this, [this](float NewValue)
		{
			CollapserImpl->SetSize(NewValue);
		}));
	}

	void Collapse()
	{
		Animator.EaseOut(CollapserImpl->GetCurrentSize(), 0.f, 10.f, 2.f,
			FFloatAnimator::FOnValueChanged::CreateWeakLambda(this, [this](float NewValue)
		{
			CollapserImpl->SetSize(NewValue);
		}));
	}

	void CollapseImmediately()
	{
		CollapserImpl->SetSizeImmediately(0.f);
	}

private:
	TUniquePtr<ICollapserImpl> CollapserImpl;
	FFloatAnimator Animator;
};
