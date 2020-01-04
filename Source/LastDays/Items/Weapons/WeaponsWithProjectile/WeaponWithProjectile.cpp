// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWithProjectile.h"
#include "Engine/World.h"
#include "TimerManager.h"

AWeaponWithProjectile::AWeaponWithProjectile()
{
}

void AWeaponWithProjectile::StartFire()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(FireTimer, this, &AWeaponWithProjectile::Fire, 60.f / RPM, true, 0.f);
	}
}

void AWeaponWithProjectile::StopFire()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(FireTimer);
	}
}

void AWeaponWithProjectile::Fire()
{
}