// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementHandlerComponent.h"
#include "Characters/BaseCharacter/BaseCharacter.h"

// Sets default values for this component's properties
UMovementHandlerComponent::UMovementHandlerComponent()
{
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
}


// Called when the game starts
void UMovementHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMovementHandlerComponent::JumpCustom()
{
	OwnerCharacter->Jump();
}

void UMovementHandlerComponent::MoveForward(float Value)
{
	OwnerCharacter->AddMovementInput(OwnerCharacter->GetActorForwardVector(), Value);
}

void UMovementHandlerComponent::MoveRight(float Value)
{
	OwnerCharacter->AddMovementInput(OwnerCharacter->GetActorRightVector(), Value);
}

void UMovementHandlerComponent::YawView(float Value)
{
	OwnerCharacter->AddControllerYawInput(Value);
}

void UMovementHandlerComponent::PitchView(float Value)
{
	OwnerCharacter->AddControllerPitchInput(Value);
}

void UMovementHandlerComponent::CrouchStart()
{
	OwnerCharacter->Crouch();
}

void UMovementHandlerComponent::CrouchEnd()
{
	OwnerCharacter->UnCrouch();
}

