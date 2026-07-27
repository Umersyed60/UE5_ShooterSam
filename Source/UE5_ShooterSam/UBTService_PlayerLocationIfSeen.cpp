// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTService_PlayerLocationIfSeen.h"

#include "ShooterAI.h"

UUBTService_PlayerLocationIfSeen::UUBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update PlayerLocation If Seen");
}

void UUBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	AUE5_ShooterSamCharacter* Player = OwnerController->PlayerCharacter;
	UBlackboardComponent* Blackboard = OwnerController->GetBlackboardComponent();

	if (OwnerController && Player && Blackboard) {
		if (OwnerController->LineOfSightTo(Player)) {
			Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
			OwnerController->SetFocus(Player);
		}
		else {
			Blackboard->ClearValue(GetSelectedBlackboardKey());
			OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}
