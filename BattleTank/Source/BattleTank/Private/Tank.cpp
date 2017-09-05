// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);

	TankBarrel = BarrelToSet;
}

void ATank::SetTurrentReference(UTankTurrent* TurrentToSet)
{
	TankAimingComponent->SetTurrentReference(TurrentToSet);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFiredInSeconds) > ReloadTimeInSeconds;

	if (TankBarrel && isReloaded)
	{
		FVector BarrelEndLocation = TankBarrel->GetSocketLocation(FName("Projectile"));
		FRotator BarrelEndRotation = TankBarrel->GetSocketRotation(FName("Projectile"));
		//UE_LOG(LogTemp, Warning, TEXT("Firing Location: %s"), *BarrelEndLocation.ToString());

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelEndLocation, BarrelEndRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiredInSeconds = FPlatformTime::Seconds();
	}
}