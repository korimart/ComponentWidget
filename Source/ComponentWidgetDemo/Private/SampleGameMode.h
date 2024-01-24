// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SampleWidgets.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SampleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASampleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// AActor
	virtual void BeginPlay() override
	{
		Super::BeginPlay();

		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly{});
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		
		const TSoftClassPtr<UMainWidget> MainWidgetClass
		{
			FSoftObjectPath{ TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP_Main.BP_Main_C'") }
		};

		MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass.LoadSynchronous());
		MainWidget->AddToViewport();
	}
	// ~AActor

private:
	UPROPERTY()
	UMainWidget* MainWidget;
};
