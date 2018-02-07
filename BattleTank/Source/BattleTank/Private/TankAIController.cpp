// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessdTank = Cast<ATank>(InPawn);
		if (!ensure(PossessdTank)) { return; }
		PossessdTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	//if (GetPlayerTank() && GetControlledTank())
	//{
	//	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	//}

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto OwnerTank = GetPawn();

	if (!ensure(PlayerTank && OwnerTank)) { return; }
	
	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
	
}


