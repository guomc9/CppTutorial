// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTutorialGameModeBase.h"

void ACppTutorialGameModeBase::InitGameState()
{
	Super::InitGameState();

	if (DefaultPawnClass == ADefaultPawn::StaticClass() || !DefaultPawnClass)
	{
		DefaultPawnClass = CustomPPawnClass;
	}
}
