// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableActor.h"

// Sets default values
ACollectableActor::ACollectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void ACollectableActor::BeginPlay()
{
	Super::BeginPlay();
	FScriptDelegate DeletgateSubscriber;
	DeletgateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DeletgateSubscriber);
	SetActorTickEnabled(false);
}

void ACollectableActor::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsLaunched && OtherActor->IsA(TriggerClass))
	{
		RunTrigger.Broadcast(OtherActor, Component);
	}
}

// Called every frame
void ACollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsLaunched)
	{
		LiveDuration -= DeltaTime;
		if (LiveDuration <= 0.0f)
		{
			Destroy();
		}
	}
}

void ACollectableActor::Run()
{
	if (!IsLaunched)
	{
		StaticMesh->AddImpulse(StaticMesh->GetMass() * Accl);

		SetActorTickEnabled(true);
		IsLaunched = true;
	}
}

void ACollectableActor::SetAccl(FVector value)
{
	Accl = value;
}

FVector ACollectableActor::GetAccl() const
{
	return this->Accl;
}

