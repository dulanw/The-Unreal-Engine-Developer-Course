// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" //TODO Remove coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	//Get Next Way Point Index
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto NextWaypointIndex = BlackboardComp->GetValueAsInt(NextWaypointIndexKey.SelectedKeyName);

	//Set Patrol Point
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[NextWaypointIndex]);


	//Cycle Index
	NextWaypointIndex = (NextWaypointIndex + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(NextWaypointIndexKey.SelectedKeyName, NextWaypointIndex);

	//UE_LOG(LogTemp, Warning, TEXT("Choose Next Waypoint executed! %s"), *OwnerComp.GetOwner()->GetName());
	return EBTNodeResult::Succeeded;
}



