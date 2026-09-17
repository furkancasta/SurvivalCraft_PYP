// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivalCraft_PYPCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SurvivalCraft_PYP.h"
#include "../../../../Program Files/Epic Games/UE_5.8/Engine/Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Module/TextureShareCoreLogDefines.h"

ASurvivalCraft_PYPCharacter::ASurvivalCraft_PYPCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	// bileseni bellekte baslatiyor
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
}

void ASurvivalCraft_PYPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASurvivalCraft_PYPCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASurvivalCraft_PYPCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASurvivalCraft_PYPCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASurvivalCraft_PYPCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ASurvivalCraft_PYPCharacter::LookInput);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASurvivalCraft_PYPCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASurvivalCraft_PYPCharacter::StopSprint);
	}
	else
	{
		UE_LOG(LogSurvivalCraft_PYP, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASurvivalCraft_PYPCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ASurvivalCraft_PYPCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ASurvivalCraft_PYPCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ASurvivalCraft_PYPCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ASurvivalCraft_PYPCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ASurvivalCraft_PYPCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ASurvivalCraft_PYPCharacter::StartSprint()
{
	if (GetCharacterMovement())
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void ASurvivalCraft_PYPCharacter::StopSprint()
{
	if (GetCharacterMovement())
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}


void ASurvivalCraft_PYPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSprinting)
	{
		CurrentStamina -= StaminaDrainRate * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);

		// Stamina bittiyse koşmayı durdur
		if (CurrentStamina <= 0.0f)
		{
			StopSprint();
		}
	}
	else
	{
		// Koşmuyorken stamina dolsun
		CurrentStamina += StaminaRegenRate * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
	}
}

float ASurvivalCraft_PYPCharacter::GetStaminaPercentage() const
{
	return CurrentStamina / MaxStamina;
}

void ASurvivalCraft_PYPCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	float FallVelocity = -GetCharacterMovement()->Velocity.Z;
	float MinFallSpeed = 625.0f;

	if (FallVelocity >= MinFallSpeed)
	{
		float BaseDamage = 30.0f;
		float ExtraDamage = (FallVelocity - MinFallSpeed) * 0.1f;
		float TotalDamage = BaseDamage + ExtraDamage;

		if (AttributeComponent)
		{
			AttributeComponent->ApplyDamage(TotalDamage);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hasar Verildi: %f"), TotalDamage));
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HATA: AttributeComponent NULL!"));
			}
		}
	}
}