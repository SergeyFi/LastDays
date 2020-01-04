// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFinderComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Characters/Human/HumanCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/ObjectInteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UObjectFinderComponent::UObjectFinderComponent()
{
	HumanOwner = Cast<AHumanCharacter>(GetOwner());
}


// Called when the game starts
void UObjectFinderComponent::BeginPlay()
{
	Super::BeginPlay();

	StartObjectFinder();
}

void UObjectFinderComponent::StartObjectFinder_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(ObjectFinderTimer, this, &UObjectFinderComponent::FindObjectToInteract, ObjectCheckPeriod, true, 0.f);
	}
}

void UObjectFinderComponent::StopObjectFinder_Implementation()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(ObjectFinderTimer);
	}
}

void UObjectFinderComponent::FindObjectToInteract_Implementation()
{
	ValidateFindObjectParameters(SphereCheckRadius, Lenght);

	InteractionObject = nullptr;
	CurrentActor = nullptr;

	TArray<FHitResult> OutHits;

	FVector StartLocation = HumanOwner->GetCameraComponent()->GetComponentLocation();
	FVector EndLocation = HumanOwner->GetCameraComponent()->GetForwardVector() * Lenght + StartLocation;

	StartLocationCopy = StartLocation;
	EndLocationCopy = EndLocation;

	bool IsHit = GetWorld()->SweepMultiByChannel(OutHits, StartLocation, EndLocation, FQuat::Identity, ECC_WorldStatic, FCollisionShape::MakeSphere(SphereCheckRadius));



	if (IsHit)
	{
		for (FHitResult HitResult : OutHits)
		{
			InteractionObject = Cast<IObjectInteractionInterface>(HitResult.Actor);

			if (InteractionObject != nullptr)
			{
				CurrentActor = HitResult.Actor.Get();
				break;
			}
		}
	}
}

void UObjectFinderComponent::UseInteractableObject_Implementation()
{
	if (InteractionObject != nullptr)
	{
		InteractionObject->Execute_Use(Cast<AActor>(InteractionObject), HumanOwner);
	}
}

bool UObjectFinderComponent::ValidateFindObjectParameters_Validate(float SphereCheckRadiusToCheck, float LenghtToCheck)
{
	return SphereCheckRadius == SphereCheckRadiusToCheck && Lenght == LenghtToCheck;
}

void UObjectFinderComponent::ValidateFindObjectParameters_Implementation(float SphereCheckRadiusToCheck, float LenghtToCheck)
{
}