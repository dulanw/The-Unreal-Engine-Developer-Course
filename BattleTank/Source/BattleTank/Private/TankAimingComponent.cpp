// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurrent* TurrentToSet)
{
	if (!BarrelToSet || !TurrentToSet) { return; }

	Turrent = TurrentToSet;	
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFiredInSeconds = FPlatformTime::Seconds();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RoundsLeft <= 0 && RoundsLoaded <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFiredInSeconds) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}

	if ((PreviousFiringStatus == EFiringStatus::Reloading && FiringStatus == EFiringStatus::Aiming) || (PreviousFiringStatus == EFiringStatus::Reloading && FiringStatus == EFiringStatus::Locked))
	{
		RoundsLoaded++;
		RoundsLeft--;
	}

	PreviousFiringStatus = FiringStatus;

	// ...
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	return !(AimDirection.Equals(Barrel->GetForwardVector(), 0.01));
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel || !Turrent) { return; }
	FVector LaunchVelocityOUT;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocityOUT, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		AimDirection = LaunchVelocityOUT.GetSafeNormal();
		MoveBarrel(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (ensure(!Barrel || !Turrent)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);

	if(FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turrent->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turrent->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (FiringStatus == EFiringStatus::Aiming || FiringStatus == EFiringStatus::Locked)
	{
		FVector BarrelEndLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator BarrelEndRotation = Barrel->GetSocketRotation(FName("Projectile"));
		//UE_LOG(LogTemp, Warning, TEXT("Firing Location: %s"), *BarrelEndLocation.ToString());

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelEndLocation, BarrelEndRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiredInSeconds = FPlatformTime::Seconds();
		RoundsLoaded--;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

FString UTankAimingComponent::GetRoundsLeft() const
{
	FString R = FString(TEXT("--"));
	if (RoundsLoaded == 0)
		R = "--";
	else if (RoundsLoaded == 1)
		R = "1";

	FString Ammo = R + "/" + FString::FromInt(RoundsLeft);

	return Ammo;
}



