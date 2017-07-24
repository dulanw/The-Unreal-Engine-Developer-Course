// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//checking if beingplay works
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller BeginPlay!"));
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No pawn possessed by AI"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AI Possesed Pawn: %s"), *(GetPawn()->GetName()) );

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No player found"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AI tank: %s found Player pawn: %s"), *(GetPawn()->GetName()), *(PlayerTank->GetName()) );

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
