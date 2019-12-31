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

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AItemBase* Item;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Condition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ObjectName;

	FInventoryItem()
	{
	}

	FInventoryItem(class AItemBase* Item, int32 ItemCount)
	{
		this->Item = Item;
		this->ItemName = Item->GetItemName();
		this->ItemCount = ItemCount;
		this->Condition = Item->GetCondition();
		this->Description = Item->GetDescription();
		Weight = Item->GetWeightTotal();
		bIsStackable = Item->IsInventoryStackable();
		ObjectName = *Item->GetName();
	}

	void AppendItem(int32 CountItem)
	{
		this->ItemCount += CountItem;
		Weight = this->ItemCount * Item->GetWeight();
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
	float WeightCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float WeightMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
	float VolumeCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float VolumeMax;

	int32 GetItemIndex(class AItemBase* Item);

	int32 ItemAmountCanAdd(class AItemBase* Item);

	void UpdateWeight();

public:

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(class AItemBase* Item);
	
	virtual void GetLifetimeReplicatedProps(TArray < class FLifetimeProperty >& OutLifetimeProps) const override;

	int32 GetItemCount();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FInventoryActionDelegate OnAddItem;
};
