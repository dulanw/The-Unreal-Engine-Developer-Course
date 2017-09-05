// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Set Throttle between +1 and -1
	UFUNCTION(BluePrintCallable, Category = Input)
		void SetThrottle(float Throttle);
	
	//Max Force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; // 48 tonne tank and 1g of acceleration
};
