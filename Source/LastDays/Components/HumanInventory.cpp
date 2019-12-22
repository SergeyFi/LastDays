// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanInventory.h"

// Sets default values for this component's properties
UHumanInventory::UHumanInventory()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Inventory default properties
	WeightMax = 10.f;
	VolumeMax = 10.f;
}


// Called when the game starts
void UHumanInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHumanInventory::AddItemToInventory_Implementation(class AItemBase* Item)
{
	int32 ItemAmount = ItemAmountCanAdd(Item);

	if (Item != nullptr && CanAddItem(Item) && ItemAmount > 0)
	{
		int32 InventoryIndex = GetItemIndex(Item);

		if (InventoryIndex == -1 || !Item->IsInventoryStackable())
		{
			// Create new inventory slot
			AItemBase* ItemDuplicated = DuplicateObject(Item, this);
			Inventory.Add(FInventoryItem(ItemDuplicated, Item->RemoveItems(ItemAmount)));
		}
		else 
		{
			// Append inventory slot
			Inventory[InventoryIndex].AppendItem(Item->RemoveItems(ItemAmount));
		}

		UpdateWeightAndVolume();
	}
}

// If item in invetory -> return inventory index else return -1
int32 UHumanInventory::GetItemIndex(AItemBase* Item)
{
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemName.EqualTo(Item->GetItemName()) && Inventory[i].Condition == Item->GetCondition())
		{
			return i;
		}
	}

	return -1;
}

bool UHumanInventory::CanAddItem(class AItemBase* Item)
{
	return true;
}

int32 UHumanInventory::ItemAmountCanAdd(AItemBase* Item)
{
	int32 ItemCanAddByWeight = (WeightMax - WeightCurrent) / Item->GetWeight();
	int32 ItemCanAddByVolume = (VolumeMax - VolumeCurrent) / Item->GetVolume();

	return FMath::Clamp(FMath::Min(ItemCanAddByWeight, ItemCanAddByVolume), 0, Item->GetItemCount());
}

void UHumanInventory::UpdateWeightAndVolume()
{
	WeightCurrent = 0.f;
	VolumeCurrent = 0.f;

	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		WeightCurrent += Inventory[i].Weight;
		VolumeCurrent += Inventory[i].Volume;
	}
}
