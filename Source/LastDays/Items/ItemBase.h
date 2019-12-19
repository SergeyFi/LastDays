// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ObjectInteractionInterface.h"
#include "ItemBase.generated.h"

UCLASS()
class LASTDAYS_API AItemBase : public AActor, public IObjectInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Base")
	FText ActionName;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactive objects")
	void Use(class AActor* InteractPerson);
	virtual void Use_Implementation(class AActor* InteractPerson);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactive objects")
	FText GetObjectName();
	virtual FText GetObjectName_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactive objects")
	FText GetActionName();
	virtual FText GetActionName_Implementation();
};
