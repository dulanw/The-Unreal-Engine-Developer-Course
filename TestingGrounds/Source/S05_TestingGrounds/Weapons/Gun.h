// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class AMannequin;

UCLASS()
class S05_TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;
	
public:	
	// Sets default values for this actor's properties
	AGun();

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Called after construction but before beingplay, after the object is spawned and/or when placed in the editor
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABallProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FPFireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* TPFireAnimation;

	class UAnimInstance* FPAnimInstance;
	class UAnimInstance* TPAnimInstance;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable)
		void OnFire();

	void TriggerPulled();
	void TriggerReleased();

	void SetOwningPawn(AMannequin* Char);

	void SetIsFirstPerson(bool SetFirstPerson);

	bool IsFirstPerson() const;

private:
	FTimerHandle FireRateTimerHandle;

	float LastFireTime = 0.f;

	AMannequin* OwnerChar = nullptr;

	bool isFirstPerson = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireRate", meta = (AllowPrivateAccess = "true"))
		float FireRate = 60.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireRate", meta = (AllowPrivateAccess = "true"))
		float TimeBetweenShots = 1.f;
};
