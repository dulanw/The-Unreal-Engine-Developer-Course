// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	/*auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f : Degrees Per Second: %f"), Time,DegreesPerSecond);*/
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,-1,+1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto NewElevation = RelativeRotation.Pitch + ElevationChange;

	NewElevation = FMath::Clamp<float>(NewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}


