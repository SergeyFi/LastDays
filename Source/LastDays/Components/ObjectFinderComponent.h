// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectFinderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTDAYS_API UObjectFinderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectFinderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class AHumanCharacter* HumanOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ObjectCheckPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SphereCheckRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Lenght;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* CurrentActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector StartLocationCopy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector EndLocationCopy;

	class IObjectInteractionInterface* InteractionObject;

	FTimerHandle ObjectFinderTimer;

	UFUNCTION(Client, Reliable)
	void StartObjectFinder();

	UFUNCTION(Client, Reliable)
	void StopObjectFinder();

	UFUNCTION(Client, Reliable)
	void FindObjectToInteract();

	UFUNCTION(Server, Unreliable, WithValidation)
	void ValidateFindObjectParameters(float SphereCheckRadiusToCheck, float LenghtToCheck);

public:

	UFUNCTION(Client, Reliable)
	void UseInteractableObject();
};
