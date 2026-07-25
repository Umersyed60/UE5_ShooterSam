// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_ShooterSamGameMode.h"

AUE5_ShooterSamGameMode::AUE5_ShooterSamGameMode()
{
	// stub
}

void AUE5_ShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Getting Player Object Reference in Gameplay
	AUE5_ShooterSamCharacter* Player = Cast<AUE5_ShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//Getting All EnemyAI Object Refrences
	TArray<AActor*> ShooterAIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);

	//for (int32 LoopIndex = 0; LoopIndex < ShooterAIActors.Num(); LoopIndex++) {
	//	AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActors[LoopIndex]);
	//	if (ShooterAI) {
	//		ShooterAI->StartBehaviorTree(Player);
	//	}
	//}

	//Ranged Based For Loop
	for (AActor* ShooterAIActor : ShooterAIActors) {
		AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);

		if (ShooterAI) {
			ShooterAI->StartBehaviorTree(Player); //Call To Start Behavior Tree Of All Fetched Enemy AI
		}
	}
}
