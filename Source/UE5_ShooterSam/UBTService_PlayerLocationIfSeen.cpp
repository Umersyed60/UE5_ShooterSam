// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTService_PlayerLocationIfSeen.h"

#include "ShooterAI.h"

//Custom Service Attached to Selector Node
UUBTService_PlayerLocationIfSeen::UUBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update PlayerLocation If Seen");
}

void UUBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	//Getting References Of EnemyAI, Player, and Blackboard
	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	AUE5_ShooterSamCharacter* Player = OwnerController->PlayerCharacter;
	UBlackboardComponent* Blackboard = OwnerController->GetBlackboardComponent();

	if (OwnerController && Player && Blackboard) {
		//Condition to Check If Having Player In LineOfSight
		if (OwnerController->LineOfSightTo(Player)) {
			//Setting Blackboard PlayerLocation Variable Value
			Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());

			OwnerController->SetFocus(Player);
		}
		else {
			//Clearing PlayerLocation Value On Losing Sight
			Blackboard->ClearValue(GetSelectedBlackboardKey());

			OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}
