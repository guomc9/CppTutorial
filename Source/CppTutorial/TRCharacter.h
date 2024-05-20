// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMesh.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ReverseTimeComponent.h"
#include "TRCharacter.generated.h"

UCLASS()
class CPPTUTORIAL_API ATRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Basic")
	TObjectPtr<UInputAction> FBAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Basic")
	TObjectPtr<UInputAction> LRAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Basic")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Basic")
	TObjectPtr<UInputAction> TimeReverseAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	void Look(const FInputActionInstance& Instance);
	void MoveLR(const FInputActionInstance& Instance);
	void MoveFB(const FInputActionInstance& Instance);
	void BeginTimeReverse(const FInputActionInstance& Instance);
	void EndTimeReverse(const FInputActionInstance& Instance);

	UPROPERTY(BlueprintReadWrite)
	UEnhancedInputComponent* Input;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly)
	UReverseTimeComponent* ReverseTime;

};
