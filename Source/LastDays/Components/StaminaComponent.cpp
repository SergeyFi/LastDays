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
	SprintWastePeriod = 0.5f;
	SprintStaminaCost = 4.f;
	JumpStaminaCost = 10.f;
	StaminaRegenerationPeriod = 1.f;
	StaminaRegenerationAmount = 1.f;

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	if (OwnerCharacter != nullptr)
	{
		OwnerCharacter->GetMovementHandler()->OnJump.AddDynamic(this, &UStaminaComponent::DecreaseStaminaOnJump);

		OwnerCharacter->GetMovementHandler()->OnSprint.AddDynamic(this, &UStaminaComponent::StartWastestaminaOnSprint);

		OwnerCharacter->GetMovementHandler()->OnStopSprint.AddDynamic(this, &UStaminaComponent::StopStaminaWasteOnStopSprint);
	}

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(StaminaRegenerationTimer, this, &UStaminaComponent::RegenerateStamina, StaminaRegenerationPeriod, true, 0.f);
	}

}


void UStaminaComponent::DecreaseStaminaOnJump_Implementation()
{
	if (StaminaCurrent >= JumpStaminaCost)
	{
		StaminaCurrent -= JumpStaminaCost;
	}

	UpdateStaminaClient(StaminaCurrent);
}


void UStaminaComponent::StartWastestaminaOnSprint_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(SprintTimer, this, &UStaminaComponent::SprintStaminaWaste, SprintWastePeriod, true, 0.f);
	}
}

void UStaminaComponent::StopStaminaWasteOnStopSprint_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(SprintTimer);
	}
}


void UStaminaComponent::SprintStaminaWaste_Implementation()
{
	StaminaCurrent -= SprintStaminaCost;

	if (StaminaCurrent <= 0)
	{
		StaminaCurrent = 0.f;

		if (OwnerCharacter != nullptr) OwnerCharacter->GetMovementHandler()->SprintStopServerClient();
	}

	UpdateStaminaClient(StaminaCurrent);
}

void UStaminaComponent::RegenerateStamina_Implementation()
{
	StaminaCurrent += StaminaRegenerationAmount;

	if (StaminaCurrent > StaminaMax) StaminaCurrent = 100.f;

	UpdateStaminaClient(StaminaCurrent);
}

void UStaminaComponent::UpdateStaminaClient_Implementation(float Stamina)
{
	StaminaCurrent = Stamina;
}

bool UStaminaComponent::CanJump()
{
	if (StaminaCurrent < JumpStaminaCost)
	{
		return false;
	}

	else return true;
}
