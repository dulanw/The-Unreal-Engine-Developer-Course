// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))
		FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

void ATankPlayerController::SetAimPointPosition(FVector2D AimPointPosition)
{
	CrosshairXLocation = AimPointPosition.X;
	CrosshairYLocation = AimPointPosition.Y;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocationOUT;
	if (GetSightHitLocation(HitLocationOUT))
	{
		AimingComponent->AimAt(HitLocationOUT);
	}
	
}

bool ATankPlayerController::GetSightHitLocation(FVector &HitLocationOUT) const
{

	//get view port size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//get the crosshair location on screen
	FVector2D ScreenLocation = FVector2D((ViewportSizeX*CrosshairXLocation), (ViewportSizeY*CrosshairYLocation));


	FVector WorldDirection;


	if (GetLookDirection(ScreenLocation,WorldDirection)) //get the screen position in the 3d world, return false if not found
	{
		return GetLookVectorHitLocation(WorldDirection, HitLocationOUT);
	}
	return false;
}



void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
	StartSpectatingOnly();
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocationOUT) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
	{
		HitLocationOUT = HitResult.Location;
		return true;
	}
	HitLocationOUT = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}