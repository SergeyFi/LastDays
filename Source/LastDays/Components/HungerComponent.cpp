// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Characters/BaseCharacter/BaseCharacter.h"
#include "Components/MovementHandlerComponent.h"

// Sets default values for this component's properties
UHungerComponent::UHungerComponent()
{
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	Thirst = 100.f;
	Starvation = 100.f;
}


// Called when the game starts
void UHungerComponent::BeginPlay()
{
	Super::BeginPlay();

	StartStarvationThirstTimer();
}


void UHungerComponent::StartStarvationThirstTimer_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr) World->GetTimerManager().SetTimer(StarvationThirstWasteTimer, this, &UHungerComponent::StarvationThirstWaste, StarvationThirstPeriod, true, 0.f);
}

void UHungerComponent::StarvationThirstWaste_Implementation()
{
	if (OwnerCharacter != nullptr)
	{
		if (OwnerCharacter->GetMovementHandler()->IsIdle())
		{
			RemoveStarvationThirst(StarvationWasteIdle, ThirstWasteIdle);
		}
		else if (OwnerCharacter->GetMovementHandler()->IsWalk())
		{
			RemoveStarvationThirst(StarvationWasteWalk, ThirstWasteIWalk);
		}
		else if (OwnerCharacter->GetMovementHandler()->IsSprint())
		{
			RemoveStarvationThirst(StarvationWasteSprint, ThirstWasteSprint);
		}
	}
}

void UHungerComponent::RemoveStarvationThirst_Implementation(float StarvationRemove, float ThirstRemove)
{
	Starvation -= StarvationRemove;
	Thirst -= ThirstRemove;

	if (Starvation <= 0.f)
	{
		Starvation = 0.f;
		OnStarving.Broadcast();
	}

	if (Thirst <= 0.f)
	{
		Thirst = 0.f;
		OnThirsty.Broadcast();
	}

	UpdateStarvationThirstClient(Starvation, Thirst);
}

void UHungerComponent::UpdateStarvationThirstClient_Implementation(float StarvationServer, float ThirstServer)
{
	Starvation = StarvationServer;
	Thirst = ThirstServer;
}

bool UHungerComponent::IsStarving()
{
	if (Starvation <= 0.f)
	{
		return true;
	}
	else return false;
}

bool UHungerComponent::IsThirsty()
{
	if (Thirst <= 0.f)
	{
		return true;
	}
	else return false;
}

float UHungerComponent::GetStarvation()
{
	return Starvation;
}

float UHungerComponent::GetThirst()
{
	return Thirst;
}
