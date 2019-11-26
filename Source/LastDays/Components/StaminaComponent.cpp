// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	StaminaMax = 100.f;
	StaminaCurrent = StaminaMax;
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

