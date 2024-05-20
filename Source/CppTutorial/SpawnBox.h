// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpawnBox.generated.h"

UCLASS()
class CPPTUTORIAL_API ASpawnBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	bool SpawnActor();


	UFUNCTION(BlueprintCallable)
	void EnableActorSpawning(bool Enable);

	void ScheduleActorSpawn();

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	UPROPERTY(EditAnywhere)
	float AvgSpawnTime = 5.0f;

	UPROPERTY(EditAnywhere)
	float RandomSpawnTimeOffset = 1.0f;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldSpawn = true;


private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;


	UFUNCTION()
	void SpawnActorScheduled();

};
