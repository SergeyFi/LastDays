// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter/BaseCharacter.h"
#include "HumanCharacter.generated.h"


UCLASS()
class LASTDAYS_API AHumanCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AHumanCharacter();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	class UObjectFinderComponent* ObjectFinder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	class UCapsuleComponent* ObjectFinderCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	class UHumanInventoryComponent* InventoryComponent;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UCameraComponent* GetCameraComponent();

	class UCapsuleComponent* GetObjectFinderCapsule();

	class UHumanInventoryComponent* GetInventoryComponent();
	
};
