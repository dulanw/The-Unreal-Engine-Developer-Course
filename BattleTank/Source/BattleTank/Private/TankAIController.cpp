// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

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

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (PlayerTank)
	{
		ATank* ControlledTank = Cast<ATank>(GetPawn());
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}

}


