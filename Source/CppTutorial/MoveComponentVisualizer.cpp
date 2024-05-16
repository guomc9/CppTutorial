// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponentVisualizer.h"

void FMoveComponentVisualizer::DrawVisualization(const UActorComponent* Comp, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	const UMoveComponent* MoveComponent = Cast<UMoveComponent>(Comp);
	if (MoveComponent)
	{
		PDI->DrawLine(
			MoveComponent->GetComponentLocation(),
			MoveComponent->GetComponentLocation() + MoveComponent->GetMoveOffset(),
			FLinearColor::Red,
			SDPG_Foreground
		);
	}
}
