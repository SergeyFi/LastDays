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

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Root);
	SkeletalMesh->SetSimulatePhysics(true);
	SkeletalMesh->SetCollisionProfileName(TEXT("Ragdoll"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(SkeletalMesh);
	SphereCollision->SetCollisionProfileName(TEXT("OverlapAll"));

	ItemName = FText::FromString(TEXT("None"));
	ActionName = FText::FromString(TEXT("None"));
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



