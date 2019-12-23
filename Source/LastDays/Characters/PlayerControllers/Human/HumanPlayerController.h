// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HumanPlayerController.generated.h"


UCLASS()
class LASTDAYS_API AHumanPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	//UFUNCTION(Client, Reliable)
	//void AddInventoryToViewport();

public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf <class UUserWidget> InventoryUIBP;

	//class UUserWidget* InventoryUI;
};
