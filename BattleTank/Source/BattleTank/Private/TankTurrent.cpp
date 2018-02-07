// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurrent.h"

void UTankTurrent::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto NewRotationChange = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotationChange,0));
}



