// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AHumanCharacter::AHumanCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cast<USceneComponent>(GetCapsuleComponent()));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 0.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 60.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}