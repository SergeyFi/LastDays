// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Characters/Human/HumanCharacter.h"
#include "Components/HumanInventory.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	// Item default properties
	StackSize = 1;
	ItemCount = StackSize;
	Condition = 100.f;
	Weight = 1.f;
	Volume = 1.f;
	bIsInventoryStackable = true;
	ItemName = FText::FromString(TEXT("None"));
	ActionName = FText::FromString(TEXT("None"));

	// Components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Root);
	SkeletalMesh->SetSimulatePhysics(true);
	SkeletalMesh->SetCollisionProfileName(TEXT("Ragdoll"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(SkeletalMesh);
	SphereCollision->SetCollisionProfileName(TEXT("OverlapAll"));
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBase::Use_Implementation(AActor* InteractPerson)
{
	AHumanCharacter* InteractCharacter = Cast<AHumanCharacter>(InteractPerson);

	InteractCharacter->GetInventoryComponent()->AddItemToInventory(this);
}

FText AItemBase::GetObjectName_Implementation()
{
	return ItemName;
}

FText AItemBase::GetActionName_Implementation()
{
	return ActionName;
}

FText AItemBase::GetItemName()
{
	return ItemName;
}

int32 AItemBase::GetItemCount()
{
	return ItemCount;
}

float AItemBase::GetCondition()
{
	return Condition;
}

float AItemBase::GetWeight()
{
	return Weight;
}

float AItemBase::GetWeightTotal()
{
	return Weight * ItemCount;
}

float AItemBase::GetVolume()
{
	return Volume;
}

float AItemBase::GetVolumeTotal()
{
	return Volume * ItemCount;
}

bool AItemBase::IsInventoryStackable()
{
	return bIsInventoryStackable;
}

int32 AItemBase::RemoveItems(int32 ItemCount)
{
	this->ItemCount -= ItemCount;

	if (this->ItemCount <= 0)
	{
		this->Destroy();
	}

	return ItemCount;
}