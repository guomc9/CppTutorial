// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MoveComponent.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveComponentReachEndPointSignature, bool, IsTopEndpoint);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTUTORIAL_API UMoveComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;
	FVector MoveOffsetNorm;

	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere)
	bool MoveEnable = true;

	FVector StartRelativeLocation;
	FVector EndRelativeLocation;

	UPROPERTY(EditAnywhere)
	float MaxDistance = 100.0f;
	UPROPERTY(EditAnywhere)
	float MinDistance = 0.0f;
	float CurDistance = 0.0f;
	float Forward = 1.0f;

	UPROPERTY(BlueprintAssignable)
	FOnMoveComponentReachEndPointSignature OnEndpointReached;

public:	
	// Sets default values for this component's properties
	UMoveComponent();
	UFUNCTION(BlueprintCallable)
	void EnbaleMovement(bool ShouldMove);
	UFUNCTION(BlueprintCallable)
	bool IsMovable() const;
	UFUNCTION(BlueprintCallable)
	FVector GetMoveOffset() const;
	UFUNCTION(BlueprintCallable)
	void SetForward();
	UFUNCTION(BlueprintCallable)
	void SetBack();
	UFUNCTION(BlueprintCallable)
	void ResetMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
