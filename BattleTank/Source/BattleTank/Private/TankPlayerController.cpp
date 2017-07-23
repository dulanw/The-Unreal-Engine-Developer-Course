// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControllledTank() const
{
	//cast the getpawn to a ATank type
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player Controller BeginPlay!") );
	auto ControlledTank = GetControllledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No pawn possessed"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Possesed Pawn: %s"), *GetPawn()->GetName());

}
