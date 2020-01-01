// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanInventoryComponent.h"
#include "Characters/Human/HumanCharacter.h"
#include "Runtime/Engine/Public/WorldCollision.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

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

	ItemsBaseOnGround.Empty();

	for (FHitResult Hit : HitResults)
	{
		AItemBase* ItemBase = Cast<AItemBase>(Hit.Actor);

		if (ItemBase != nullptr)
		{
			ItemsBaseOnGround.AddUnique(ItemBase);
		}
	}

	ItemsBaseOnGround.Sort();

	for (AItemBase* Item : ItemsBaseOnGround)
	{
		if (Item != nullptr)
		{
			ItemsOnGround.Add(FInventoryItem(Item, Item->GetItemCount()));
		}
	}
}

void UHumanInventoryComponent::AddItemFromGround_Implementation(FItemData ItemDataGround)
{
	for (AItemBase* ItemBase : ItemsBaseOnGround)
	{
		if (ItemBase != nullptr)
		{
			if (ItemBase->GetItemData() == ItemDataGround)
			{
				AddItemToInventory(ItemBase);
				break;
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
		ItemsOnGroundCount += InventoryItem.ItemCount;
	}

	return ItemsOnGroundCount;
}

void UHumanInventoryComponent::DropItemFromInventory_Implementation(FItemData ItemData)
{

	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemData == ItemData)
		{
			UWorld* World = GetWorld();

			if (World != nullptr)
			{
				FActorSpawnParameters SpawnParams;

				FTransform SpawnTransform = HumanOwner->GetTransform() + ObjectDropTransform;
				AItemBase* ItemToSpawn = World->SpawnActorDeferred<AItemBase>(Inventory[i].ItemData.BPItem, SpawnTransform);

				ItemToSpawn->SetItemData(ItemData);
				ItemToSpawn->SetItemCount(Inventory[i].RemoveItem());

				if (Inventory[i].ItemCount == 0) Inventory.RemoveAt(i);

				UGameplayStatics::FinishSpawningActor(ItemToSpawn, SpawnTransform);

				break;
			}
		}
	}
}