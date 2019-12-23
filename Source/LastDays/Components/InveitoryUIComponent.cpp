// Fill out your copyright notice in the Description page of Project Settings.


#include "InveitoryUIComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UInveitoryUIComponent::UInveitoryUIComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UInveitoryUIComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//InventoryUI = CreateWidget<UUserWidget>(Cast<APlayerController>(GetOwner()), InventoryUIBP);
}

