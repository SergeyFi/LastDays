// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Net/UnrealNetwork.h"

// Inventory component - that component is used to implement the inventory system in items

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bReplicates = true;
	bNetAddressable = true;

	// Inventory default properties
	CapacityMax = 10.f;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UInventoryComponent, Inventory, COND_OwnerOnly);
}

void UInventoryComponent::AddItemToInventory_Implementation(class AItemBase* Item)
{
	OnAddItem.Broadcast();

	if (Item != nullptr)
	{
		int32 ItemAmount = ItemAmountCanAdd(Item);

		if (ItemAmount > 0)
		{
			int32 InventoryIndex = GetItemIndex(Item);

			if (InventoryIndex == -1 || !Item->IsInventoryStackable())
			{
				// Create new inventory slot
				Inventory.Add(FInventoryItem(Item, Item->RemoveItems(ItemAmount)));
			}
			else
			{
				// Append inventory slot
				Inventory[InventoryIndex].AppendItem(Item->RemoveItems(ItemAmount));
			}

			UpdateCapacity();

			OnAddItem.Broadcast();
		}
	}
}

// If item in invetory -> return inventory index else return -1
int32 UInventoryComponent::GetItemIndex(AItemBase* Item)
{
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemData == Item->GetItemData())
		{
			return i;
		}
	}

	return -1;
}

int32 UInventoryComponent::ItemAmountCanAdd(AItemBase* Item)
{
	int32 ItemCanAddByWeight = (CapacityMax - CapacityCurrent) / Item->GetCapacity();

	return FMath::Clamp(ItemCanAddByWeight, 0, Item->GetItemCount());
}

void UInventoryComponent::UpdateCapacity()
{
	CapacityCurrent = 0.f;

	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		CapacityCurrent += Inventory[i].Capacity;
	}
}

int32 UInventoryComponent::GetItemCount()
{
	int32 TotalItemCount = 0;

	for (FInventoryItem Item : Inventory)
	{
		TotalItemCount += Item.ItemCount;
	}

	return TotalItemCount;
}