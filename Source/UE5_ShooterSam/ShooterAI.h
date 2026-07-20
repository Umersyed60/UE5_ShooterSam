// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Kismet/GameplayStatics.h"

#include "ShooterAI.generated.h"

/**
 * 
 */
UCLASS()
class UE5_SHOOTERSAM_API AShooterAI : public AAIController
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AShooterAI();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	APawn* PlayerPawn;
};
