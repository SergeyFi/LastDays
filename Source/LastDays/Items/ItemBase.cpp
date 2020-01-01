// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Characters/Human/HumanCharacter.h"
#include "Components/HumanInventoryComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

// Item base - base class in inventory system

// Sets default values
AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	// Item default properties
	StackSize = 1;
	ItemCount = StackSize;
	Condition = 100.f;
	Capacity = 1.f;
	bIsInventoryStackable = true;
	ItemName = FText::FromString(TEXT("None"));
	ActionName = FText::FromString(TEXT("None"));
	Description = FText::FromString(TEXT("None"));
	BPItem = this->GetClass();

	// Components	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetSimulatePhysics(true);
	SkeletalMesh->SetCollisionProfileName(TEXT("Ragdoll"));
	RootComponent = SkeletalMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(SkeletalMesh);
	SphereCollision->SetCollisionProfileName(TEXT("OverlapAll"));
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	if (Capacity == 0.f) Capacity = 0.001;
	
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

void AItemBase::SetItemCount(int32 ItemCount)
{
	this->ItemCount = ItemCount;
}

float AItemBase::GetCondition()
{
	return Condition;
}

float AItemBase::GetCapacity()
{
	return Capacity;
}

float AItemBase::GetCapacityTotal()
{
	return Capacity * ItemCount;
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

FText AItemBase::GetDescription()
{
	return Description;
}

TSubclassOf<AItemBase> AItemBase::GetBPItem()
{
	return BPItem;
}

FItemData AItemBase::GetItemData()
{
	return FItemData(Condition, BPItem);
}

void AItemBase::SetItemData(FItemData& ItemData)
{
	Condition = ItemData.Condition;
}

USkeletalMeshComponent* AItemBase::GetMesh()
{
	return SkeletalMesh;
}

int32 AItemBase::GetStackSize()
{
	return StackSize;
}
