// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/InputComponent.h"
#include "Components/MovementHandlerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementHandlerComponent = CreateDefaultSubobject<UMovementHandlerComponent>(TEXT("MovementHanlder"));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, MovementHandlerComponent, &UMovementHandlerComponent::JumpCustom);

	PlayerInputComponent->BindAxis("MoveForward", MovementHandlerComponent, &UMovementHandlerComponent::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight", MovementHandlerComponent, &UMovementHandlerComponent::MoveRight);

	PlayerInputComponent->BindAxis("YawView", MovementHandlerComponent, &UMovementHandlerComponent::YawView);

	PlayerInputComponent->BindAxis("PitchView", MovementHandlerComponent, &UMovementHandlerComponent::PitchView);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, MovementHandlerComponent, &UMovementHandlerComponent::CrouchStart);

	PlayerInputComponent->BindAction("Crouch", IE_Released, MovementHandlerComponent, &UMovementHandlerComponent::CrouchEnd);
}

