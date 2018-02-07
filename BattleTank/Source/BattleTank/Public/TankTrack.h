// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Set Throttle between +1 and -1
	UFUNCTION(BluePrintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	
	//Max Force per track, in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Custom")
		float TrackMaxDrivingForce = 400000; // 48 tonne tank and 1g of acceleration

private:
	UTankTrack();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
		float MaxForwardVelocity = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
		float MaxUpVelocity = 50.f;

	//Max Velocity of tank, in cm/s
	
};
