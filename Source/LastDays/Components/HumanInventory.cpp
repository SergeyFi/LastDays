// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanInventory.h"
#include "Items/ItemBase.h"

// Sets default values for this component's properties
UHumanInventory::UHumanInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHumanInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHumanInventory::AddItemToInventory_Implementation(class AItemBase* Item)
{
	if (CanAddItem(Item))
	{
		//Inventory.Add(Cast<AItemBase>(DuplicateObject(Item, this)));
		Item->Destroy();
	}
}

bool UHumanInventory::CanAddItem(class AItemBase* Item)
{
	return true;
}


