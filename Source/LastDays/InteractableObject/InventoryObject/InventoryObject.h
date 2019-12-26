// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject/InteractableObject.h"
#include "InventoryObject.generated.h"


UCLASS()
class LASTDAYS_API AInventoryObject : public AInteractableObject
{
	GENERATED_BODY()

public:

	AInventoryObject();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	class UInventoryComponent* InventoryComponent;
};
