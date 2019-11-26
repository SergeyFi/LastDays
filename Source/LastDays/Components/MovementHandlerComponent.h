// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementHandlerComponent.generated.h"


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

	UFUNCTION(Server, Reliable)
	void SprintStartServer();

	UFUNCTION(Server, Reliable)
	void SprintStopServer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	bool bCanSprint;

public:

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void JumpCustom();

	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void YawView(float Value);

	void PitchView(float Value);

	void CrouchStart();

	void CrouchEnd();

	void SprintStart();

	void SprintStop();
};
