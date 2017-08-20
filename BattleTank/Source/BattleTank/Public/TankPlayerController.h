// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  //put new includes above this


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControllledTank() const;

	//move the tank barrel toward where the crosshair is pointed toward
	void AimTowardsCrosshair();
	bool GetSightHitLocation(FVector &HitLocationOUT) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.50f;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.350f;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocationOUT) const;

protected:
	virtual void BeginPlay() override;


public:
	//our begin play overrides the original.
	virtual void Tick(float DeltaTime) override;
	void SetAimPointPosition(FVector2D AimPointPosition);
	
};
