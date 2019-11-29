// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	HealthMax = 100.f;
	HealthCurrent = HealthMax;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::RemoveHealth_Implementation(float Damage)
{
	HealthCurrent -= Damage;

	if (HealthCurrent <= 0.f)
	{
		HealthCurrent = 0.f;

		OnDeath.Broadcast();
	}

	UpdateHealthClient(HealthCurrent);
}

void UHealthComponent::UpdateHealthClient_Implementation(float Health)
{
	HealthCurrent = Health;
}