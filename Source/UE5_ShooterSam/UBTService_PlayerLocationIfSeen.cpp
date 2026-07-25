// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTService_PlayerLocationIfSeen.h"

UUBTService_PlayerLocationIfSeen::UUBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update PlayerLocation If Seen");
}

void UUBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UE_LOG(LogTemp, Display, TEXT("Service is Ticking: %f"), DeltaSeconds);
}
