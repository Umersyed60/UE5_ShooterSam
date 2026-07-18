// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"


// Sets default values
AShooterAI::AShooterAI()
{
}

// Called when the game starts or when spawned
void AShooterAI::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		SetFocus(PlayerPawn);
	}
}