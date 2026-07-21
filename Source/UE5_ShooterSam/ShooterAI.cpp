// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"


// Sets default values
AShooterAI::AShooterAI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterAI::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void AShooterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LineOfSightTo(PlayerPawn)) {
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn, 200.0f);
	}
	else {
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}