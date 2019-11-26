// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementHandlerComponent.h"
#include "Characters/BaseCharacter/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaminaComponent.h"

// Sets default values for this component's properties
UMovementHandlerComponent::UMovementHandlerComponent()
{
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	WalkSpeed = 600.f;
	SprintSpeed = 900.f;
	bCanSprint = true;
}


// Called when the game starts
void UMovementHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (OwnerCharacter != nullptr) OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void UMovementHandlerComponent::JumpCustom()
{
	if (OwnerCharacter != nullptr) OwnerCharacter->Jump();
}

void UMovementHandlerComponent::MoveForward(float Value)
{
	if (OwnerCharacter != nullptr) OwnerCharacter->AddMovementInput(OwnerCharacter->GetActorForwardVector(), Value);
}

void UMovementHandlerComponent::MoveRight(float Value)
{
	if (OwnerCharacter != nullptr) OwnerCharacter->AddMovementInput(OwnerCharacter->GetActorRightVector(), Value);
}

void UMovementHandlerComponent::YawView(float Value)
{
	if (OwnerCharacter != nullptr) OwnerCharacter->AddControllerYawInput(Value);
}

void UMovementHandlerComponent::PitchView(float Value)
{
	if (OwnerCharacter != nullptr) OwnerCharacter->AddControllerPitchInput(Value);
}

void UMovementHandlerComponent::CrouchStart()
{
	if ( OwnerCharacter != nullptr ) OwnerCharacter->Crouch();
}

void UMovementHandlerComponent::CrouchEnd()
{
	if (OwnerCharacter != nullptr) OwnerCharacter->UnCrouch();
}

void UMovementHandlerComponent::SprintStart()
{
	if (OwnerCharacter != nullptr && bCanSprint)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

		SprintStartServer();
	}
}

void UMovementHandlerComponent::SprintStop()
{
	if (OwnerCharacter != nullptr)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

		SprintStopServer();
	}
}

void UMovementHandlerComponent::SprintStartServer_Implementation()
{
	if (OwnerCharacter != nullptr && bCanSprint)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void UMovementHandlerComponent::SprintStopServer_Implementation()
{
	if (OwnerCharacter != nullptr)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}
