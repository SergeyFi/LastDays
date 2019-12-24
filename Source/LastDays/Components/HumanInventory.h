// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemBase.h"
#include "HumanInventory.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AItemBase* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ItemCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Condition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Weight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Volume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsStackable;

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
		Volume = Item->GetVolumeTotal();
		bIsStackable = Item->IsInventoryStackable();
	}

	void AppendItem(int32 CountItem)
	{
		this->ItemCount += CountItem;
		Weight = this->ItemCount * Item->GetWeight();
		Volume = this->ItemCount * Item->GetVolume();
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTDAYS_API UHumanInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHumanInventory(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
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

	void UpdateWeightAndVolume();

	UFUNCTION(Client, Reliable)
	void UpdateInventoryClient(const TArray<FInventoryItem> &InventoryServer);

public:
	UPROPERTY(Replicated)
	uint32 bReplicatedFlag : 1;

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

	UFUNCTION(Server, Reliable)
	void AddItemToInventory(class AItemBase* Item);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void UpdateInventory();
};
