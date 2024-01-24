// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


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
