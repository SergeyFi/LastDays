// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UHungerComponent::UHungerComponent()
{

}


// Called when the game starts
void UHungerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHungerComponent::StartStarvationThirstTimer_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr) World->GetTimerManager().SetTimer(StarvationThirstWasteTimer, this, &UHungerComponent::StartStarvationThirstTimer, 1.f, true, 0.f);
}

void UHungerComponent::StarvationThirstWaste_Implementation()
{
	UpdateStarvationThirstClient(Starvation, Thirst);
}

void UHungerComponent::UpdateStarvationThirstClient_Implementation(float StarvationServer, float ThirstServer)
{
	Starvation = StarvationServer;
	Thirst = ThirstServer;
}
