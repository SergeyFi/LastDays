// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ObjectFinderComponent.h"
#include "Components/InputComponent.h"
#include "Components/HumanInventoryComponent.h"


AHumanCharacter::AHumanCharacter()
{
	SetReplicates(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cast<USceneComponent>(GetCapsuleComponent()));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 0.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 60.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ObjectFinder = CreateDefaultSubobject<UObjectFinderComponent>(TEXT("ObjectFinder"));

	ObjectFinderCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ObjectFinderCapsule"));
	ObjectFinderCapsule->SetupAttachment(Cast<USceneComponent>(Camera));
	ObjectFinderCapsule->SetCapsuleHalfHeight(120.f);
	ObjectFinderCapsule->SetCapsuleRadius(30.f);
	ObjectFinderCapsule->SetRelativeLocation(FVector(130.f, 0.f, 0.f));
	ObjectFinderCapsule->SetRelativeRotation(FQuat(180.f, -90.f, 180.f, 0.f));

	InventoryComponent = CreateDefaultSubobject<UHumanInventoryComponent>(TEXT("InventoryComponent"));
	InventoryComponent->SetIsReplicated(true);
}

void AHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Use", IE_Pressed, ObjectFinder, &UObjectFinderComponent::UseInteractableObject);
}

UCameraComponent* AHumanCharacter::GetCameraComponent()
{
	return Camera;
}

UCapsuleComponent* AHumanCharacter::GetObjectFinderCapsule()
{
	return ObjectFinderCapsule;
}

UHumanInventoryComponent* AHumanCharacter::GetInventoryComponent()
{
	return InventoryComponent;
}
