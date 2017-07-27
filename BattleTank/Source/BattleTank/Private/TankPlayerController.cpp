// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


ATank* ATankPlayerController::GetControllledTank() const
{
	//cast the getpawn to a ATank type
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	///testing to see if tick function works as intended
	///UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking!"));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControllledTank()) { return; }
	
	FVector HitLocationOUT;
	if (GetSightHitLocation(HitLocationOUT))
	{
		GetControllledTank()->AimAt(HitLocationOUT);
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
		GetLookVectorHitLocation(WorldDirection, HitLocationOUT);
	}
	return true;
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