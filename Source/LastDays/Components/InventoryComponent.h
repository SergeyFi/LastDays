// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemBase.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryActionDelegate);

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

protected:

	void CalculateCapacity()
	{
		AItemBase* DefaultObject = ItemData.BPItem.GetDefaultObject();
		
		if (DefaultObject != nullptr) Capacity = ItemCount * DefaultObject->GetCapacity();
	}

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Capacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStackable;

	FInventoryItem()
	{
	}

	FInventoryItem(class AItemBase* Item, int32 ItemCount)
	{
		this->ItemData = Item->GetItemData();
		this->ItemCount = ItemCount;
		Capacity = Item->GetCapacityTotal();
		bIsStackable = Item->IsInventoryStackable();

		CalculateCapacity();
	}

	void AppendItem(int32 CountItem)
	{
		this->ItemCount += CountItem;
		CalculateCapacity();
	}

	int32 GetRemovedItem()
	{
		AItemBase* DefaultObject = ItemData.BPItem.GetDefaultObject();

		if (ItemCount <= DefaultObject->GetStackSize())
		{
			int32 ItemCountToDrop = ItemCount;
			ItemCount = 0;

			return ItemCountToDrop;
		}
		else
		{
			int32 ItemCountToDrop = DefaultObject->GetStackSize();
			ItemCount -= ItemCountToDrop;

			return ItemCountToDrop;
		}
	}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTDAYS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", Replicated)
	TArray<FInventoryItem> Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
	float CapacityCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float CapacityMax;

	int32 GetItemIndex(class AItemBase* Item);

	int32 ItemAmountCanAdd(class AItemBase* Item);

	void UpdateCapacity();

public:

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(class AItemBase* Item);
	
	virtual void GetLifetimeReplicatedProps(TArray < class FLifetimeProperty >& OutLifetimeProps) const override;

	int32 GetItemCount();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FInventoryActionDelegate OnAddItem;
};
