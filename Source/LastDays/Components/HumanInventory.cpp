// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanInventory.h"
#include "UnrealNetwork.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHumanInventory::UHumanInventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	bReplicates = true;

	// Inventory default properties
	WeightMax = 10.f;
	VolumeMax = 10.f;
}

void UHumanInventory::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHumanInventory, bReplicatedFlag);
}


// Called when the game starts
void UHumanInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHumanInventory::AddItemToInventory_Implementation(class AItemBase* Item)
{
	int32 ItemAmount = ItemAmountCanAdd(Item);

	if (Item != nullptr && ItemAmount > 0)
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
		UpdateInventory();
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

void UHumanInventory::UpdateInventoryClient_Implementation(const TArray<FInventoryItem> &InventoryServer)
{
	Inventory = InventoryServer;
}

void UHumanInventory::UpdateInventory_Implementation()
{
	UpdateInventoryClient(Inventory);
}
