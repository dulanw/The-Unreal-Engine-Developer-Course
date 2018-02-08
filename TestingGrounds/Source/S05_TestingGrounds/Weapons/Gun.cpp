// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Animation/AnimInstance.h"
#include "BallProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Mannequin.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	//FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//FP_Gun->bCastDynamicShadow = false;
	//FP_Gun->CastShadow = false;
	//FP_Gun->SetHiddenInGame(false);
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 68.4f, 10.6f));
	FP_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	
}

//run after construction but before beingplay, after the object is spawned and/or when placed in the editor
void AGun::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TimeBetweenShots = 60 / FireRate;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Owner: %s"), *GetOwner()->GetName());
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL && isFirstPerson)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{			
			const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			//const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
			const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FPFireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		//UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (FPAnimInstance != NULL)
		{
			FPAnimInstance->Montage_Play(FPFireAnimation, 1.f);

		}
	}

	if (TPFireAnimation != NULL)
	{
		if (TPAnimInstance != NULL)
		{
			TPAnimInstance->Montage_Play(TPFireAnimation,1.f);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AGun::OnFire, TimeBetweenShots, false);
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void AGun::TriggerPulled()
{
	//UE_LOG(LogTemp, Warning, TEXT("Timer Started!"));
	const float GameTime = GetWorld()->GetTimeSeconds();
	bool bTooSoon = TimeBetweenShots > GameTime - LastFireTime;
	if (bTooSoon)
	{
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AGun::OnFire,  TimeBetweenShots + LastFireTime - GameTime, false);
	}
	else
	{
		OnFire();
	}
	
}

void AGun::TriggerReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
}

void AGun::SetOwningPawn(AMannequin* Char)
{
	OwnerChar = Char;
	SetOwner(Char);
}

void AGun::SetIsFirstPerson(bool SetFirstPerson)
{
	isFirstPerson = SetFirstPerson;
	if (SetFirstPerson)
	{
		FP_Gun->bOnlyOwnerSee = true;
		FP_Gun->bOwnerNoSee = false;
		FP_Gun->bCastDynamicShadow = false;
		FP_Gun->CastShadow = false;
	}
	else
	{
		FP_Gun->bOnlyOwnerSee = false;
		FP_Gun->bOwnerNoSee = true;

		//cast shadows for third person weapon
		FP_Gun->bCastDynamicShadow = true;
		FP_Gun->CastShadow = true;
		FP_Gun->bCastHiddenShadow = true;
	}
}

bool AGun::IsFirstPerson() const
{
	return isFirstPerson;
}
