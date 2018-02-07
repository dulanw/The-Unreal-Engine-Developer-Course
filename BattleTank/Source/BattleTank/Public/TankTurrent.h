// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurrent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurrent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 25.f;
	//UPROPERTY(EditAnywhere, Category = Setup)
	//	float MaxElevationDegrees = 35.f;
	//UPROPERTY(EditAnywhere, Category = Setup)
	//	float MinElevationDegrees = 0.f;
	
};
