// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBase::Use_Implementation(AActor* InteractPerson)
{
	Destroy();
}

FText AItemBase::GetObjectName_Implementation()
{
	return ItemName;
}

FText AItemBase::GetActionName_Implementation()
{
	return ActionName;
}



