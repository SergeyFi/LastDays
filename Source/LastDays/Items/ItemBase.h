// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ObjectInteractionInterface.h"
#include "ItemBase.generated.h"

// Item base - base class in inventory system

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Condition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class AItemBase> BPItem;

	FItemData(){}

	FItemData(float Condition, TSubclassOf<class AItemBase> BPItem)
	{
		this->Condition = Condition;
		this->BPItem = BPItem;
	}

	bool operator == (const FItemData &ItemData)
	{
		return Condition == ItemData.Condition && BPItem == ItemData.BPItem;
	}
};

UCLASS()
class LASTDAYS_API AItemBase : public AActor, public IObjectInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	FText ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	TSubclassOf<AItemBase> BPItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	float Condition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	bool bIsInventoryStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	int32 ItemCount;
		

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactive objects")
	void Use(class AActor* InteractPerson);
	virtual void Use_Implementation(class AActor* InteractPerson) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactive objects")
	FText GetObjectName();
	virtual FText GetObjectName_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactive objects")
	FText GetActionName();
	virtual FText GetActionName_Implementation() override;

	FText GetItemName();

	int32 GetItemCount();

	void SetItemCount(int32 ItemCount);

	float GetCondition();

	float GetWeight();

	float GetWeightTotal();

	bool IsInventoryStackable();

	int32 RemoveItems(int32 ItemCount);

	FText GetDescription();

	TSubclassOf<AItemBase> GetBPItem();

	virtual FItemData GetItemData();

	virtual void SetItemData(FItemData& ItemData);

	USkeletalMeshComponent* GetMesh();

	int32 GetStackSize();
};
