// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanInventoryComponent.h"
#include "Characters/Human/HumanCharacter.h"
#include "Runtime/Engine/Public/WorldCollision.h"
#include "Engine/World.h"
#include "TimerManager.h"

UHumanInventoryComponent::UHumanInventoryComponent()
{
	HumanOwner = Cast<AHumanCharacter>(GetOwner());

	SphereGroundChecker = FCollisionShape::MakeSphere(CheckRadius);
}

void UHumanInventoryComponent::StartCheckGround()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(GroundCheckTimer, this, &UHumanInventoryComponent::CheckGround, GroundCheckPeriod, true, 0.f);
	}
}

void UHumanInventoryComponent::StopCheckGround()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(GroundCheckTimer);
	}
}

void UHumanInventoryComponent::CheckGround()
{
	FVector Location = HumanOwner->GetActorLocation();

	TArray<FHitResult> OutHits;

	bool bIsHit = GetWorld()->SweepMultiByChannel(OutHits, Location, Location, FQuat::Identity, ECC_WorldStatic, SphereGroundChecker);

	if (bIsHit)
	{
		AddActorToGroundItem(OutHits);
	}
}

void UHumanInventoryComponent::AddActorToGroundItem(TArray<FHitResult> HitResults)
{
	ItemsOnGround.Empty();

	AItemBase* Item;

	for (FHitResult Hit : HitResults)
	{
		Item = Cast<AItemBase>(Hit.Actor);

		if (Item != nullptr)
		{
			ItemsOnGround.Add(Item);
		}
	}
}