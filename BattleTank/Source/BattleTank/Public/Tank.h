// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //put new includes above this

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	//return current health as percentage of starting health
	UFUNCTION(BlueprintPure, Category = "Health")
		float getPercentHealth() const;

	FTankDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly,Category = "Health")
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;
};
