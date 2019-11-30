// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTDAYS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float HealthCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthCicleRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthRegenerationMultiplier;

	UFUNCTION(Client, Reliable)
	void UpdateHealthClient(float Health);

	UFUNCTION(Server, Reliable)
	void StartMainHealthCicle();

	UFUNCTION(Server, Reliable)
	void MainHealthCicle();

	UFUNCTION(Server, Reliable)
	void HealthRegeneration();

	FTimerHandle MainHealthTimer;


	// Other
	class ABaseCharacter* OwnerCharacter;


	// Hunger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hunger")
	float StarvingDamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hunger")
	float ThirstDamageAmount;

	UFUNCTION(Server, Reliable)
	void HungerDamage();
public:

	UFUNCTION(Server, Reliable)
	void RemoveHealth(float Damage);

	UFUNCTION(Server, Reliable)
	void AddHealth(float Heal);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FDeathDelegate OnHealthEnded;

};
