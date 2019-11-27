// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"
#include "Characters/BaseCharacter/BaseCharacter.h"
#include "Components/MovementHandlerComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	StaminaMax = 100.f;
	StaminaCurrent = StaminaMax;
	SprintWastePeriod = 0.5f;
	SprintStaminaCost = 4.f;
	JumpStaminaCost = 10.f;
	StaminaRegenerationRate = 2.f;
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
		OwnerCharacter->GetMovementHandler()->OnJump.AddDynamic(this, &UStaminaComponent::DecreaseStaminaJumpServerClient);

		OwnerCharacter->GetMovementHandler()->OnSprint.AddDynamic(this, &UStaminaComponent::StaminaWasteStartServerClient);

		OwnerCharacter->GetMovementHandler()->OnStopSprint.AddDynamic(this, &UStaminaComponent::StaminaWasteStopServerClient);
	}
}

void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RegenerateStaminaServer(DeltaTime);
	RegenerateStaminaClient(DeltaTime);
}


void UStaminaComponent::DecreaseStaminaJumpServerClient_Implementation()
{
	if (StaminaCurrent >= JumpStaminaCost)
	{
		StaminaCurrent -= JumpStaminaCost;
	}
	else
	{
		bCanJump = false;
	}

	DecreaseStaminaJumpClient();
}

void UStaminaComponent::DecreaseStaminaJumpClient_Implementation()
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

void UStaminaComponent::StaminaWasteStartServerClient_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(SprintTimer, this, &UStaminaComponent::SprintWasteServer, SprintWastePeriod, true, 0.f);
	}

	StaminaWasteStartClient();
}

void UStaminaComponent::StaminaWasteStopServerClient_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(SprintTimer);
	}

	StaminaWasteStopClient();
}


void UStaminaComponent::SprintWasteServer_Implementation()
{
	StaminaCurrent -= SprintStaminaCost;

	if (StaminaCurrent <= 0)
	{
		StaminaCurrent = 0.f;
		bCanSprint = false;

		if (OwnerCharacter != nullptr) OwnerCharacter->GetMovementHandler()->SprintStopServerClient();

		StaminaWasteStopServerClient();
	}
}

void UStaminaComponent::SprintWasteClient_Implementation()
{
	StaminaCurrent -= SprintStaminaCost;

	if (StaminaCurrent <= 0)
	{
		StaminaCurrent = 0.f;
		bCanSprint = false;

		if (OwnerCharacter != nullptr) OwnerCharacter->GetMovementHandler()->SprintStopServerClient();

		StaminaWasteStopServerClient();
	}
}



void UStaminaComponent::RegenerateStaminaServer_Implementation(float DeltaTime)
{
	StaminaCurrent += StaminaRegenerationRate * DeltaTime;

	if (StaminaCurrent > StaminaMax) StaminaCurrent = 100.f;

	if (StaminaCurrent >= JumpStaminaCost) bCanJump = true;
}

void UStaminaComponent::RegenerateStaminaClient_Implementation(float DeltaTime)
{
	StaminaCurrent += StaminaRegenerationRate * DeltaTime;

	if (StaminaCurrent > StaminaMax) StaminaCurrent = 100.f;

	if (StaminaCurrent >= JumpStaminaCost) bCanJump = true;
}