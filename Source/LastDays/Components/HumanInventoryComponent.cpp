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

	TArray<AItemBase*> ItemBaseOnGround;

	for (FHitResult Hit : HitResults)
	{
		AItemBase* ItemBase = Cast<AItemBase>(Hit.Actor);

		if (ItemBase != nullptr)
		{
			ItemBaseOnGround.AddUnique(ItemBase);
		}
	}

	ItemBaseOnGround.Sort();

	for (AItemBase* Item : ItemBaseOnGround)
	{
		if (Item != nullptr)
		{
			ItemsOnGround.Add(FInventoryItem(Item, Item->GetItemCount()));
		}
	}
}

void UHumanInventoryComponent::AddItemFromGround_Implementation(AItemBase* ItemGround)
{
	if (ItemGround != nullptr)
	{
		for (FInventoryItem InventoryItem : ItemsOnGround)
		{
			if (InventoryItem.Item == ItemGround)
			{
				AddItemToInventory(ItemGround);
			}
		}
	}
}


bool UHumanInventoryComponent::GroundItemIsChanged()
{
	static int32 ItemOnGroundCount;

	int32 ItemsOnGroundCountCurrent = GetItemsOnGroundCount();

	if (ItemOnGroundCount != ItemsOnGroundCountCurrent)
	{
		ItemOnGroundCount = ItemsOnGroundCountCurrent;

		return true;
	}

	return false;
}

bool UHumanInventoryComponent::InventoryIsChanged()
{
	static int32 ItemCount;

	int32 CurrentItemCount = GetItemCount();
	if (ItemCount != CurrentItemCount)
	{
		ItemCount = CurrentItemCount;

		return true;
	}

	return false;
}

int32 UHumanInventoryComponent::GetItemsOnGroundCount()
{
	int32 ItemsOnGroundCount = 0;

	for (FInventoryItem InventoryItem : ItemsOnGround)
	{
		if (InventoryItem.Item != nullptr)
		{
			ItemsOnGroundCount += InventoryItem.Item->GetItemCount();
		}
	}

	return ItemsOnGroundCount;
}

void UHumanInventoryComponent::DropItemFromInventory_Implementation(const FString &ObjectName)
{
	UE_LOG(LogTemp, Warning, TEXT("DropItemFromInventory start"));

	for (FInventoryItem InventoryItem : Inventory)
	{
		if (InventoryItem.ObjectName.Equals(ObjectName))
		{
			UWorld* World = GetWorld();

			UE_LOG(LogTemp, Warning, TEXT("Item found"));

			if (World != nullptr && InventoryItem.Item != nullptr)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Template = InventoryItem.Item;

				FTransform SpawnTransform = HumanOwner->GetTransform() + ObjectDropTransform;

				World->SpawnActor<AItemBase>(InventoryItem.Item->GetBPItem(), SpawnTransform, SpawnParams);

				UE_LOG(LogTemp, Warning, TEXT("Item spawned"));
			}
		}
	}
}