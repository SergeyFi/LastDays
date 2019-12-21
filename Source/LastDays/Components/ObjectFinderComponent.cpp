// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFinderComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Characters/Human/HumanCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/ObjectInteractionInterface.h"

// Sets default values for this component's properties
UObjectFinderComponent::UObjectFinderComponent()
{
	HumanOwner = Cast<AHumanCharacter>(GetOwner());
}


// Called when the game starts
void UObjectFinderComponent::BeginPlay()
{
	Super::BeginPlay();

	if (HumanOwner != nullptr) HumanOwner->GetObjectFinderCapsule()->OnComponentBeginOverlap.AddDynamic(this, &UObjectFinderComponent::OnOverlapBegin);
	if (HumanOwner != nullptr) HumanOwner->GetObjectFinderCapsule()->OnComponentEndOverlap.AddDynamic(this, &UObjectFinderComponent::OnOverlapEnd);

}

void UObjectFinderComponent::UseInteractableObject_Implementation()
{
	if (InteractableObject != nullptr)
	{
		IObjectInteractionInterface* InteractionInterface = Cast<IObjectInteractionInterface>(InteractableObject);

		if (InteractionInterface != nullptr)
		{
			InteractionInterface->Execute_Use(InteractableObject, HumanOwner);
		}
	}

}

void UObjectFinderComponent::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IObjectInteractionInterface* InteractionInterface = Cast<IObjectInteractionInterface>(OtherActor);

	if (InteractionInterface)
	{
		InteractableObject = OtherActor;
		UpdateInterObjectOnClient(OtherActor);
	}
}

void UObjectFinderComponent::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractableObject = nullptr;
	UpdateInterObjectOnClient(nullptr);
}

void UObjectFinderComponent::UpdateInterObjectOnClient_Implementation(AActor* InterObject)
{
	InteractableObject = InterObject;
}

