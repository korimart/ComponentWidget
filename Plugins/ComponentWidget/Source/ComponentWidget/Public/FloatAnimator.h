// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


/**
 * Float 값을 특정 값에서 출발시켜 특정 값까지 연속적으로 이동시키고 싶을 때 사용하는 클래스
 *
 * 1. FFloatAnimator::Tick 을 매 틱 호출해줍니다.
 * 2. EaseOut과 같은 값 이동 함수를 호출하면 값의 변화를 Callback 함수로 받을 수 있습니다.
 */
class FFloatAnimator
{
public:
	DECLARE_DELEGATE_OneParam(FOnValueChanged, float);

	void EaseOut(float InInit, float InTarget, float InExp, float InSpeed, FOnValueChanged InOnValueChanged)
	{
		Init = InInit;
		Target = InTarget;
		Exp = InExp;
		Speed = InSpeed;
		OnValueChanged = InOnValueChanged;

		Alpha = 0.f;
	}

	void Tick(float DeltaTime)
	{
		if (Alpha >= 1.f)
		{
			return;
		}

		Alpha = FMath::FInterpConstantTo(Alpha, 1.f, DeltaTime, Speed);
		OnValueChanged.ExecuteIfBound(FMath::InterpEaseOut(Init, Target, Alpha, Exp));
	}

private:
	float Init;
	float Target;
	float Exp;
	float Speed;
	FOnValueChanged OnValueChanged;

	float Alpha = 2.f;
};
