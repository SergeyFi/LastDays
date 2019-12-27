// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanInventoryComponent.h"
#include "Characters/Human/HumanCharacter.h"
#include "Runtime/Engine/Public/WorldCollision.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// HumanInventory component - that component is used to implement the inventory system in human like characters

UHumanInventoryComponent::UHumanInventoryComponent()
{
	CheckRadius = 200.f;
	GroundCheckPeriod = 0.2;

	HumanOwner = Cast<AHumanCharacter>(GetOwner());

	SphereGroundChecker = FCollisionShape::MakeSphere(CheckRadius);

}

void UHumanInventoryComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UHumanInventoryComponent, ItemsOnGround, COND_OwnerOnly);
}

void UHumanInventoryComponent::StartCheckGround_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(GroundCheckTimer, this, &UHumanInventoryComponent::CheckGround, GroundCheckPeriod, true, 0.f);
	}
}

void UHumanInventoryComponent::StopCheckGround_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(GroundCheckTimer);

		ItemsOnGround.Empty();
	}
}

void UHumanInventoryComponent::CheckGround()
{
	FVector Location = HumanOwner->GetActorLocation();

	TArray<FHitResult> OutHits;

	bool bIsHit = GetWorld()->SweepMultiByChannel(OutHits, Location, Location + 1.f, FQuat::Identity, ECC_WorldStatic, SphereGroundChecker);

	if (bIsHit)
	{
		AddActorToGroundItem(OutHits);
	}
}

void UHumanInventoryComponent::AddActorToGroundItem(TArray<FHitResult> HitResults)
{
	ItemsOnGround.Empty();

	AItemBase* Item = nullptr;

	for (FHitResult Hit : HitResults)
	{
		Item = Cast<AItemBase>(Hit.Actor);

		if (Item != nullptr)
		{
			ItemsOnGround.AddUnique(Item);
			ItemsOnGround.Sort();
		}
	}
}