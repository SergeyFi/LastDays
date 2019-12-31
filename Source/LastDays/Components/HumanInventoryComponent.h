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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", Replicated)
	TArray<FInventoryItem> ItemsOnGround;

	TArray<AActor*> InventoriesOnGround;

	FTimerHandle GroundCheckTimer;

	struct FCollisionShape SphereGroundChecker;

	void CheckGround();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float CheckRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float GroundCheckPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	FTransform ObjectDropTransform;

	void AddActorToGroundItem(TArray<FHitResult> HitResults);

	UFUNCTION(BlueprintCallable)
	bool GroundItemIsChanged();

	UFUNCTION(BlueprintCallable)
	bool InventoryIsChanged();

public:

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void StartCheckGround();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void StopCheckGround();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AddItemFromGround(AItemBase* ItemGround);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void DropItemFromInventory(const FString& ObjectName);

	virtual void GetLifetimeReplicatedProps(TArray < class FLifetimeProperty >& OutLifetimeProps) const override;

	int32 GetItemsOnGroundCount();

};
