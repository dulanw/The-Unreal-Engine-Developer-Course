// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  //put new includes above this

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	//move the tank barrel toward where the crosshair is pointed toward
	void AimTowardsCrosshair();
	bool GetSightHitLocation(FVector &HitLocationOUT) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.0f;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.0f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnPossessedTankDeath();

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocationOUT) const;

protected:
	virtual void BeginPlay() override;

	// Use this instead of being play to make sure that aiming component is there before calling the rest on blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);


public:
	//our begin play overrides the original.
	virtual void Tick(float DeltaTime) override;
	void SetAimPointPosition(FVector2D AimPointPosition);
	
};
