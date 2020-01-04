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

	TArray<AItemBase*> ItemsBaseOnGround;

	TArray<AActor*> InventoriesOnGround;

	FTimerHandle GroundCheckTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float CheckRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float GroundCheckPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float ObjectDropDistance;

	UFUNCTION(Server, Reliable)
	void CheckGround();

	UFUNCTION(Server, Reliable)
	void AddActorToGroundItem(const TArray<FHitResult> &HitResults);

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
	void AddItemFromGround(FItemData ItemDataGround);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void DropItemFromInventory(FItemData ItemData);

	virtual void GetLifetimeReplicatedProps(TArray < class FLifetimeProperty >& OutLifetimeProps) const override;

	int32 GetItemsOnGroundCount();

};
