// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Get Patrol Points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	//auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is missing patrol points!"), *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	//Get Next Way Point Index
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto NextWaypointIndex = BlackboardComp->GetValueAsInt(NextWaypointIndexKey.SelectedKeyName);

	//Set Patrol Point
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[NextWaypointIndex]);

	//Cycle Index
	NextWaypointIndex = (NextWaypointIndex + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(NextWaypointIndexKey.SelectedKeyName, NextWaypointIndex);

	return EBTNodeResult::Succeeded;
}



