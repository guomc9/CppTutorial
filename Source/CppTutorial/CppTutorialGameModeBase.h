// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/DefaultPawn.h"
#include "PPawn.h"

#include "CppTutorialGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CPPTUTORIAL_API ACppTutorialGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void InitGameState() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<APPawn> CustomPPawnClass = APPawn::StaticClass();
};
