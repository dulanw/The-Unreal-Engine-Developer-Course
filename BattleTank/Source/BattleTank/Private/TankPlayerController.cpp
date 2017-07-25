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

	//No need for the code below, just testing to make sure the the functions work as intended
	//sdfsdf
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller BeginPlay!") );
	//if (!GetControllledTank())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("No pawn possessed"));
	//}
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("Player Possesing Pawn: %s"), *(GetPawn()->GetName()) );
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
	
	FVector HitLocation;
	if (GetSightHitLocation(HitLocation))
	{
		GetControllledTank()->AimAt(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightHitLocation(FVector &HitLocationOUT) const
{

	//get view port size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//get the crosshair location on screen
	FVector2D ScreenLocation = FVector2D((ViewportSizeX*CrosshairXLocation), (ViewportSizeY*CrosshairYLocation));

	///output crosshair position
	//UE_LOG(LogTemp, Warning, TEXT("Crosshair Screen Location: %s"), *ScreenLocation.ToString());

	FVector WorldLocation, WorldDirection;


	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection)) //get the screen position in the 3d world, return false if not found
	{
		//UE_LOG(LogTemp, Warning, TEXT("Crosshair Screen Location: %s Direction: %s"), *WorldLocation.ToString(),*WorldDirection.ToString());
		if (GetLookVectorHitLocation(WorldDirection, HitLocationOUT))
			return true;
		return false;
	}
	return false;
}



bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocationOUT) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
	{
		HitLocationOUT = HitResult.Location;
		//get the object that is hit
		//UE_LOG(LogTemp,Warning,TEXT("Hit Actor: %s"),*HitResult.GetActor()->GetName())
		return true;
	}
	return false;
}