// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"

//Custom Service Attached to Chase Node
UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Get Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Getting Player and Blackboard References
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (PlayerPawn && Blackboard) {
		//Setting Blackboard LastKnownPlayerLocation
		Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
}
