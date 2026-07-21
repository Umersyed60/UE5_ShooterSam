// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_ShooterSamGameMode.h"

AUE5_ShooterSamGameMode::AUE5_ShooterSamGameMode()
{
	// stub
}

void AUE5_ShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	AUE5_ShooterSamCharacter* Player = Cast<AUE5_ShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	TArray<AActor*> ShooterAIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);

	for (int i = 0; i < ShooterAIActors.Num(); i++) {
		AShooterAI* EnemyAI = Cast<AShooterAI>(ShooterAIActors[i]);

		EnemyAI->StartBehaviorTree(Player);
	}
}
