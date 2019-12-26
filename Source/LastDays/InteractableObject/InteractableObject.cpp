// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Set components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

