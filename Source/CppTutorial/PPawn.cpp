// Fill out your copyright notice in the Description page of Project Settings.


#include "PPawn.h"

// Sets default values
APPawn::APPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	RootComponent = PlayerMesh;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(PlayerMesh);
}

// Called when the game starts or when spawned
void APPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (!InputMappingContext.IsNull())
			{
				InputSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input && FBAction && LRAction)
	{
		Input->BindAction(FBAction, ETriggerEvent::Triggered, this, &APPawn::MoveFB);
		Input->BindAction(LRAction, ETriggerEvent::Triggered, this, &APPawn::MoveLR);
	}
}

void APPawn::MoveLR(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	FVector Location = GetActorLocation();
	Location.X += Value;
	SetActorLocation(Location);
}

void APPawn::MoveFB(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	FVector Location = GetActorLocation();
	Location.Y += Value;
	SetActorLocation(Location);
}
