// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollectAcceptable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCollectAcceptable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPPTUTORIAL_API ICollectAcceptable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Collect(UObject* SourceObj, float count);
};
