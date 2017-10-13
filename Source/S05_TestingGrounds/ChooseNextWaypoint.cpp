// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	auto NextWaypointIndex = BlackboardComp->GetValueAsInt(NextWaypointIndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Choose Next Waypoint executed! %s"), *OwnerComp.GetOwner()->GetName());
	return EBTNodeResult::Succeeded;
}



