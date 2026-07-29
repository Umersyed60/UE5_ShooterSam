// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "ShooterAI.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot At Player");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	//Getting ShooterAI Reference
	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());

	//Setting EnemyAI And Player References
	AUE5_ShooterSamCharacter* OwnerCharacter = OwnerController->MyCharacter;
	AUE5_ShooterSamCharacter* PlayerCharacter = OwnerController->PlayerCharacter;

	//Condition to Shoot At Player If Alive
	if (OwnerCharacter && PlayerCharacter && PlayerCharacter->IsAlive) {
		OwnerCharacter->Shoot();
		Result = EBTNodeResult::Succeeded;
	}

	return Result;
}
