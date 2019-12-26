// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryObject.h"
#include "Components/InventoryComponent.h"

// Object with inventory

AInventoryObject::AInventoryObject()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}