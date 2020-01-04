// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WeaponBase.h"
#include "WeaponWithProjectile.generated.h"


UCLASS()
class LASTDAYS_API AWeaponWithProjectile : public AWeaponBase
{
	GENERATED_BODY()

public:
	AWeaponWithProjectile();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties | Weapon")
		float RPM;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties | Weapon")
		int32 MagazineCapacityCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties | Weapon")
		int32 MagazineCapacityMax;

	FTimerHandle FireTimer;

	virtual void Fire();

public:

	virtual void StartFire() override;

	virtual void StopFire() override;
	
};
