// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacter.h"

// Sets default values
APCharacter::APCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	// Setup component hierarchy
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetCapsuleComponent());
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void APCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input && FBAction && LRAction && LookAction)
	{
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APCharacter::Look);
		Input->BindAction(FBAction, ETriggerEvent::Triggered, this, &APCharacter::MoveFB);
		Input->BindAction(LRAction, ETriggerEvent::Triggered, this, &APCharacter::MoveLR);
	}
}

void APCharacter::Look(const FInputActionInstance& Instance)
{
	FVector2D Value = Instance.GetValue().Get<FVector2D>();
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(-1.0f * Value.Y);

}

void APCharacter::MoveLR(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	FVector Location = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	Location += (Forward * Value);
	SetActorLocation(Location);
}

void APCharacter::MoveFB(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	FVector Location = GetActorLocation();
	FVector Right = GetActorRightVector();
	Location += (Right * Value);
	SetActorLocation(Location);
}

