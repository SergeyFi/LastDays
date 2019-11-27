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

	FTimerHandle SprintTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float StaminaMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	float StaminaCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float JumpStaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float SprintStaminaCost;

	UFUNCTION()
	void DecreaseStaminaJump();

	UFUNCTION(Server, Reliable)
	void DecreaseStaminaJumpServer();

	UFUNCTION(Client, Reliable)
	void SprintWasteClient();

	UFUNCTION(Server, Reliable)
	void SprintWasteServer();

	UFUNCTION(Client, Reliable)
	void StaminaWasteStartClient();

	UFUNCTION(Client, Reliable)
	void StaminaWasteStopClient();

	UFUNCTION(Server, Reliable)
	void StaminaWasteStartServer();

	UFUNCTION(Server, Reliable)
	void StaminaWasteStopServer();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	bool bCanJump;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	bool bCanSprint;
};
