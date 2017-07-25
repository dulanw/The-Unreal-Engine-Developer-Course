// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

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
		UPROPERTY(EditAnywhere)
			float CrosshairXLocation = 0.5f;
		UPROPERTY(EditAnywhere)
			float CrosshairYLocation = 0.33333f;
		UPROPERTY(EditAnywhere)
			float LineTraceRange = 1000000;
		bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocationOUT) const;

public:
		//our begin play overrides the original.
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
	
};
