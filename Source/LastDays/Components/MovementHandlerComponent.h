// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementHandlerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTDAYS_API UMovementHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class ABaseCharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsMoveForward;

	UFUNCTION(Client, Reliable)
	void SprintStartClient();

	UFUNCTION(Client, Reliable)
	void SprintStopClient();

	UFUNCTION(Server, Reliable)
	void CheckIsMoveForward(float value);

	UFUNCTION(Client, Reliable)
	void UpdateIsMoveForwardClient(bool MoveForward);

public:

	UFUNCTION(Server, Reliable)
	void JumpCustomServer();

	UFUNCTION(Client, Reliable)
	void JumpCustomClient();

	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void YawView(float Value);

	void PitchView(float Value);

	void CrouchStart();

	void CrouchEnd();

	UFUNCTION(Server, Reliable)
	void SprintStartServer();

	UFUNCTION(Server, Reliable)
	void SprintStopServerClient();

	UPROPERTY(BlueprintAssignable, Category = "Movement")
	FActionDelegate OnJump;

	UPROPERTY(BlueprintAssignable, Category = "Movement")
	FActionDelegate OnSprint;

	UPROPERTY(BlueprintAssignable, Category = "Movement")
	FActionDelegate OnStopSprint;

	UFUNCTION(BlueprintPure, Category = "Movement")
	float GetCurrentSpeed();

	UFUNCTION(BlueprintPure, Category = "Movement")
	bool IsIdle();

	UFUNCTION(BlueprintPure, Category = "Movement")
	bool IsWalk();

	UFUNCTION(BlueprintPure, Category = "Movement")
	bool IsSprint();
};
