// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Characters/BaseCharacter/BaseCharacter.h"
#include "Components/HungerComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	HealthMax = 100.f;
	HealthCurrent = HealthMax;

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (OwnerCharacter != nullptr) StartMainHealthCicle();
}

void UHealthComponent::MainHealthCicle_Implementation()
{
	HealthRegeneration();

	HungerDamage();

	UE_LOG(LogTemp, Warning, TEXT("MainHealthCicle"));
}

void UHealthComponent::AddHealth_Implementation(float Heal)
{
	HealthCurrent += Heal;

	if (HealthCurrent > HealthMax)
	{
		HealthCurrent = HealthMax;
	}
}

void UHealthComponent::RemoveHealth_Implementation(float Damage)
{
	HealthCurrent -= Damage;

	if (HealthCurrent <= 0.f)
	{
		HealthCurrent = 0.f;

		OnHealthEnded.Broadcast();
	}

	UpdateHealthClient(HealthCurrent);
}

void UHealthComponent::UpdateHealthClient_Implementation(float Health)
{
	HealthCurrent = Health;
}

void UHealthComponent::StartMainHealthCicle_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(MainHealthTimer, this, &UHealthComponent::MainHealthCicle, HealthCicleRate, true, 0.f);
	}
}

void UHealthComponent::HealthRegeneration_Implementation()
{
	if (HealthCurrent < HealthMax)
	{
		if (!OwnerCharacter->GetHungerComponent()->IsStarving() && !OwnerCharacter->GetHungerComponent()->IsThirsty())
		{
			float Thirst = OwnerCharacter->GetHungerComponent()->GetThirst();
			float Starvation = OwnerCharacter->GetHungerComponent()->GetStarvation();

			AddHealth(HealthRegenerationMultiplier * ((Thirst + Starvation) / 2.f));
		}
	}
}

void UHealthComponent::HungerDamage_Implementation()
{
	if (OwnerCharacter->GetHungerComponent()->IsStarving())
	{
		RemoveHealth(StarvingDamageAmount);
	}

	if (OwnerCharacter->GetHungerComponent()->IsThirsty())
	{
		RemoveHealth(ThirstDamageAmount);
	}
}