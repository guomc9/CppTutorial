// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PPawn.generated.h"

UCLASS()
class CPPTUTORIAL_API APPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveLR(const FInputActionInstance& Instance);
	void MoveFB(const FInputActionInstance& Instance);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<UInputAction> FBAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<UInputAction> LRAction;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	TObjectPtr<UInputMappingContext> InputMappingContext;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

};
