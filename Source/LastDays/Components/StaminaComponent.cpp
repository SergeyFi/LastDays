// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"
#include "Characters/BaseCharacter/BaseCharacter.h"
#include "Components/MovementHandlerComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	StaminaMax = 100.f;
	StaminaCurrent = StaminaMax;
	JumpStaminaCost = 10.f;
	bCanJump = true;
	bCanSprint = true;

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	if (OwnerCharacter != nullptr)
	{
		OwnerCharacter->GetMovementHandler()->OnJump.AddDynamic(this, &UStaminaComponent::DecreaseStaminaJump);

		OwnerCharacter->GetMovementHandler()->OnSprint.AddDynamic(this, &UStaminaComponent::StaminaWasteStartServer);

		OwnerCharacter->GetMovementHandler()->OnStopSprint.AddDynamic(this, &UStaminaComponent::StaminaWasteStopServer);
	}
}

void UStaminaComponent::DecreaseStaminaJump()
{
	if (StaminaCurrent >= JumpStaminaCost)
	{
		StaminaCurrent -= JumpStaminaCost;
	}
	else
	{
		bCanJump = false;
	}

	DecreaseStaminaJumpServer();
}


void UStaminaComponent::DecreaseStaminaJumpServer_Implementation()
{
	if (StaminaCurrent >= JumpStaminaCost)
	{
		StaminaCurrent -= JumpStaminaCost;
	}
	else
	{
		bCanJump = false;
	}

}

void UStaminaComponent::StaminaWasteStartClient_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(SprintTimer, this, &UStaminaComponent::SprintWasteClient, SprintWastePeriod, true, 0.f);
	}
}

void UStaminaComponent::StaminaWasteStopClient_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(SprintTimer);
	}
}

void UStaminaComponent::StaminaWasteStartServer_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(SprintTimer, this, &UStaminaComponent::SprintWasteServer, SprintWastePeriod, true, 0.f);
	}

	StaminaWasteStartClient();
}

void UStaminaComponent::StaminaWasteStopServer_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(SprintTimer);
	}

	StaminaWasteStopClient();
}

void UStaminaComponent::SprintWasteClient_Implementation()
{
	if (StaminaCurrent > 0.f)
	{
		StaminaCurrent -= SprintStaminaCost;
	}
	else
	{
		StaminaCurrent = 0.f;
		bCanSprint = false;

		if (OwnerCharacter != nullptr) OwnerCharacter->GetMovementHandler()->SprintStopServer();

		StaminaWasteStopServer();
	}
}

void UStaminaComponent::SprintWasteServer_Implementation()
{
	if (StaminaCurrent > 0.f)
	{
		StaminaCurrent -= SprintStaminaCost;
	}
	else
	{
		StaminaCurrent = 0.f;
		bCanSprint = false;

		if (OwnerCharacter != nullptr) OwnerCharacter->GetMovementHandler()->SprintStopServer();

		StaminaWasteStopServer();
	}
}