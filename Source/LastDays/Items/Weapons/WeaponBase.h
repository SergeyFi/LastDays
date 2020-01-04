// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "WeaponBase.generated.h"


UCLASS()
class LASTDAYS_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()

public:
	AWeaponBase();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties | Weapon")
	float Damage;

public:

	UFUNCTION(Server, Reliable)
	virtual void StartFire();

	UFUNCTION(Server, Reliable)
	virtual void StopFire();

	UFUNCTION(Server, Reliable)
	virtual void Reload();
	
};
