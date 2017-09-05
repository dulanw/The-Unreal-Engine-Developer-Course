// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //put new includes above this

class UTankBarrel;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
		void SetTurrentReference(UTankTurrent* TurrentToSet);

	UFUNCTION(BlueprintCallable)
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent * TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent * TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 5.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* TankBarrel = nullptr;


	double LastFiredInSeconds = 0;
};
