// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTDAYS_API UHungerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHungerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	float Starvation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	float Thirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float StarvationThirstPeriod;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float StarvationWasteIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float ThirstWasteIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float StarvationWasteWalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float ThirstWasteIWalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float StarvationWasteSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float ThirstWasteSprint;

	FTimerHandle StarvationThirstWasteTimer;

	UFUNCTION(Server, Reliable)
	void StartStarvationThirstTimer();

	UFUNCTION(Server, Reliable)
	void StarvationThirstWaste();

	UFUNCTION(Client, Reliable)
	void UpdateStarvationThirstClient(float StarvationServer, float ThirstServer);
};
