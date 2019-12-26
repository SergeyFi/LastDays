// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InventoryComponent.h"
#include "HumanInventoryComponent.generated.h"


UCLASS()
class LASTDAYS_API UHumanInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:

	UHumanInventoryComponent();

protected:

	class AHumanCharacter* HumanOwner;

	TArray<AItemBase*> ItemsOnGround;

	TArray<AActor*> InventoriesOnGround;

	FTimerHandle GroundCheckTimer;

	struct FCollisionShape SphereGroundChecker;

	void CheckGround();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float CheckRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float GroundCheckPeriod;

	void AddActorToGroundItem(TArray<FHitResult> HitResults);

public:

	void StartCheckGround();

	void StopCheckGround();

};
