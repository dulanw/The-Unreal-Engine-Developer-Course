// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
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

