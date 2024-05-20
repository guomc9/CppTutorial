// Fill out your copyright notice in the Description page of Project Settings.


#include "TRCharacter.h"

// Sets default values
ATRCharacter::ATRCharacter()
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
	ReverseTime = CreateDefaultSubobject<UReverseTimeComponent>(TEXT("ReverseTime"));
	//ReverseTime->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void ATRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
	Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input && FBAction && LRAction && LookAction && TimeReverseAction)
	{
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATRCharacter::Look);
		Input->BindAction(FBAction, ETriggerEvent::Triggered, this, &ATRCharacter::MoveFB);
		Input->BindAction(LRAction, ETriggerEvent::Triggered, this, &ATRCharacter::MoveLR);
		Input->BindAction(TimeReverseAction, ETriggerEvent::Started, this, &ATRCharacter::BeginTimeReverse);
		Input->BindAction(TimeReverseAction, ETriggerEvent::Completed, this, &ATRCharacter::EndTimeReverse);
	}
}

void ATRCharacter::Look(const FInputActionInstance& Instance)
{
	FVector2D Value = Instance.GetValue().Get<FVector2D>();
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(-1.0f * Value.Y);

}

void ATRCharacter::MoveLR(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	FVector Location = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	Location += (Forward * Value);
	SetActorLocation(Location);
}

void ATRCharacter::MoveFB(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	FVector Location = GetActorLocation();
	FVector Right = GetActorRightVector();
	Location += (Right * Value);
	SetActorLocation(Location);
}

void ATRCharacter::BeginTimeReverse(const FInputActionInstance& Instance)
{
	bool Value = Instance.GetValue().Get<bool>();
	FString Message = FString::Printf(TEXT("Time Reverse Started."));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Message);
	if (Value)
	{
		Message = FString::Printf(TEXT("Pressed R."));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Message);
		ReverseTime->TimeManager->BeginTimeReverse();
	}
}

void ATRCharacter::EndTimeReverse(const FInputActionInstance& Instance)
{
	bool Value = Instance.GetValue().Get<bool>();
	FString Message = FString::Printf(TEXT("Time Reverse Ended."));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Message);
	if (!Value)
	{
		Message = FString::Printf(TEXT("Released R."));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Message);
		ReverseTime->TimeManager->EndTimeReverse();
	}
}
