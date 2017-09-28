// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	//if (GetPlayerTank() && GetControlledTank())
	//{
	//	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	//}

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(!PlayerTank || !AimingComponent)) { return; }
	
	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
}


