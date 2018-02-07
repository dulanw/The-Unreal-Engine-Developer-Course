// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"  //put new includes above this

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnPossessedTankDeath();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 10000.0f;

};
