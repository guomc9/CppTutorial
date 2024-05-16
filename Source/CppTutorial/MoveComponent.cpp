// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMoveComponent::EnbaleMovement(bool ShouldMove)
{
	MoveEnable = ShouldMove;
	SetComponentTickEnabled(MoveEnable);
}

bool UMoveComponent::IsMovable() const
{
	return MoveEnable;
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	StartRelativeLocation = GetRelativeLocation();
	MoveOffsetNorm = MoveOffset;
	MoveOffsetNorm.Normalize();

	SetComponentTickEnabled(MoveEnable);
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurDistance += DeltaTime * Speed * Forward;
	if (CurDistance >= MaxDistance || CurDistance <= MinDistance)
	{
		Forward = Forward * -1.0f;
		OnEndpointReached.Broadcast(CurDistance >= MaxDistance);
		CurDistance = FMath::Clamp(CurDistance, MinDistance, MaxDistance);
	}
	SetRelativeLocation(StartRelativeLocation + MoveOffsetNorm * CurDistance);
}


FVector UMoveComponent::GetMoveOffset() const
{
	return MoveOffset;
}

void UMoveComponent::SetForward()
{
	Forward = 1.0f;
}

void UMoveComponent::SetBack()
{
	Forward = -1.0f;
}

void UMoveComponent::ResetMovement()
{
	CurDistance = 0.0f;
	SetRelativeLocation(StartRelativeLocation);
}
