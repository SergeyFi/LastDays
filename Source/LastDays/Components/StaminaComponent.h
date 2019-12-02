// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTDAYS_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class ABaseCharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float SprintWastePeriod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float StaminaRegenerationPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float StaminaRegenerationAmount;

	FTimerHandle SprintTimer;

	FTimerHandle StaminaRegenerationTimer;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float StaminaMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	float StaminaCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float JumpStaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float SprintStaminaCost;

	UFUNCTION(Server, Reliable)
	void DecreaseStaminaOnJump();

	UFUNCTION(Server, Reliable)
	void SprintStaminaWaste();

	UFUNCTION(Server, Reliable)
	void StartWastestaminaOnSprint();

	UFUNCTION(Server, Reliable)
	void StopStaminaWasteOnStopSprint();

	UFUNCTION(Server, Reliable)
	void RegenerateStamina();

	UFUNCTION(Client, Reliable)
	void UpdateStaminaClient(float Stamina);

public:
	UFUNCTION()
	bool CanJump();
};
