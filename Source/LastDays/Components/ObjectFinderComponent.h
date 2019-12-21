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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* InteractableObject;

	UFUNCTION(Server, Reliable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(Client, Reliable)
	void UpdateInterObjectOnClient(class AActor* InterObject);

public:

	UFUNCTION(Server, Reliable)
	void UseInteractableObject();
};
