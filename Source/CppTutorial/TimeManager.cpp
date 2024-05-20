// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

// Sets default values
ATimeManager::ATimeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float ATimeManager::GetTimeFactor()
{
	return CurrentTimeFactor;
}

bool ATimeManager::GetAbilityAvailable()
{
	return TimeReversalAbilityEnabled && CurrentRecordedTime >= ReverseTimeThreshold;
}

float ATimeManager::GetCurrentReversableTime()
{
	return CurrentRecordedTime;
}


void ATimeManager::BeginTimeReverse()
{
	if (TimeReversalAbilityEnabled && CurrentRecordedTime >= ReverseTimeThreshold)
	{
		CurrentTimeFactor = ReverseTimeFactor;
	}
}

void ATimeManager::EndTimeReverse()
{
	CurrentTimeFactor = NormalTimeFactor;
}

void ATimeManager::EnableTimeReverseAbility()
{
	if (!TimeReversalAbilityEnabled)
	{
		TimeReversalAbilityEnabled = true;
	}
}

void ATimeManager::DisableTimeReverseAbility()
{
	if (TimeReversalAbilityEnabled)
	{
		EndTimeReverse();
		CurrentRecordedTime = 0.0f;
		TimeReversalAbilityEnabled = false;
	}
}

void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TimeReversalAbilityEnabled)
	{
		CurrentRecordedTime = TMathUtil<float>::Min(ReverseTimeMaximum, CurrentRecordedTime + DeltaTime * CurrentTimeFactor);
		if (CurrentRecordedTime <= 0.0f)
		{
			EndTimeReverse();
			CurrentRecordedTime = 0.0f;
		}
	}
}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	CurrentTimeFactor = NormalTimeFactor;
}


