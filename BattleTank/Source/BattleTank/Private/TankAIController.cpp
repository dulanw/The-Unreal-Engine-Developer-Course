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
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAIController::GetControlledTank() const
{
	//cast the getpawn to a ATank type
	return Cast<ATank>(GetPawn());
}

