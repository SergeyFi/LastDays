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

}


// Called when the game starts
void UMovementHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (OwnerCharacter != nullptr) OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

void UMovementHandlerComponent::JumpCustomServer_Implementation()
{
	if (OwnerCharacter != nullptr && OwnerCharacter->GetCharacterMovement()->IsWalking())
	{
		if (OwnerCharacter->GetStaminaComponent()->CanJump())
		{
			OwnerCharacter->Jump();

			OnJump.Broadcast();

			JumpCustomClient();
		}
	}
}

void UMovementHandlerComponent::JumpCustomClient_Implementation()
{
	if (OwnerCharacter != nullptr && OwnerCharacter->GetCharacterMovement()->IsWalking())
	{
		if (OwnerCharacter->GetStaminaComponent()->CanJump())
		{
			OwnerCharacter->Jump();
		}
	}
}


void UMovementHandlerComponent::MoveForward(float Value)
{
	if (OwnerCharacter != nullptr)
	{
		OwnerCharacter->AddMovementInput(OwnerCharacter->GetActorForwardVector(), Value);

		CheckIsMoveForward(Value);
	}
}

void UMovementHandlerComponent::CheckIsMoveForward_Implementation(float Value)
{
	if (Value > 0.f)
	{
		bIsMoveForward = true;
	}
	else
	{
		bIsMoveForward = false;
		SprintStopServerClient();
	}

	UpdateIsMoveForwardClient(bIsMoveForward);
}

void UMovementHandlerComponent::UpdateIsMoveForwardClient_Implementation(bool MoveForward)
{
	bIsMoveForward = MoveForward;
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

void UMovementHandlerComponent::SprintStartServer_Implementation()
{
	if (OwnerCharacter != nullptr && !OwnerCharacter->GetMovementComponent()->Velocity.IsZero() && bIsMoveForward)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

		OnSprint.Broadcast();

		SprintStartClient();
	}
}

void UMovementHandlerComponent::SprintStopServerClient_Implementation()
{
	if (OwnerCharacter != nullptr)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

		OnStopSprint.Broadcast();

		SprintStopClient();
	}
}

void UMovementHandlerComponent::SprintStartClient_Implementation()
{
	if (OwnerCharacter != nullptr && !OwnerCharacter->GetMovementComponent()->Velocity.IsZero())
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void UMovementHandlerComponent::SprintStopClient_Implementation()
{
	if (OwnerCharacter != nullptr)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

float UMovementHandlerComponent::GetCurrentSpeed()
{
	if (OwnerCharacter != nullptr)
	{
		return OwnerCharacter->GetVelocity().Size();;
	}

	else return 0.f;
}

bool UMovementHandlerComponent::IsIdle()
{
	if (GetCurrentSpeed() == 0.f || OwnerCharacter->GetCharacterMovement()->IsFalling())
	{
		return true;
	}
	else return false;
}

bool UMovementHandlerComponent::IsWalk()
{
	if ((int32)GetCurrentSpeed() > 0 && (int32)GetCurrentSpeed() <= (int32)WalkSpeed && OwnerCharacter->GetCharacterMovement()->IsWalking())
	{
		return true;
	}

	else return false;
}

bool UMovementHandlerComponent::IsSprint()
{
	if ((int32)GetCurrentSpeed() > (int32)WalkSpeed && OwnerCharacter->GetCharacterMovement()->IsWalking())
	{
		return true;
	}

	else return false;
}