// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	int32 ItemCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Weight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Volume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsStackable;

	FInventoryItem()
	{
		Item = nullptr;
		ItemName = FText::FromString(TEXT("None"));
		ItemCount = 0;
		Weight = 0.f;
		Volume = 0.f;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTDAYS_API UHumanInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHumanInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	TArray<FInventoryItem> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float WeightCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float WeightMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float VolumeCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float VolumeMax;

public:

	UFUNCTION(Server, Reliable)
	void AddItemToInventory(class AItemBase* Item);

	bool CanAddItem(class AItemBase* Item);
		
};
