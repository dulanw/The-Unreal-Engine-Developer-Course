// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetNotifyRigidBodyCollision(true);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.f;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	

	FVector CurrentVelocity = GetComponentVelocity();
	FVector NewForwardVelocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0);

	if (NewForwardVelocity.Size() > MaxForwardVelocity)
	{
		NewForwardVelocity = NewForwardVelocity.GetClampedToSize(0, MaxForwardVelocity);
		NewForwardVelocity = FVector(NewForwardVelocity.X, NewForwardVelocity.Y, CurrentVelocity.Z);

		SetAllPhysicsLinearVelocity(NewForwardVelocity, false);
	}

	

	//UE_LOG(LogTemp, Warning, TEXT("UpVector = %f"), NewUpVelocity.Size());

	//if (GetComponentVelocity().Z > 1)
	//{
	//	FVector NewUpVelocity = FVector(0, 0, GetComponentVelocity().Z);
	//	if (NewUpVelocity.Size() > MaxUpVelocity)
	//	{
	//		NewUpVelocity = NewUpVelocity.GetClampedToSize(0, MaxUpVelocity);
	//		NewUpVelocity = FVector(GetComponentVelocity().X, GetComponentVelocity().Y, -GetComponentVelocity().Z);
	//		SetAllPhysicsLinearVelocity(NewUpVelocity, false);

	//		//auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	//		//auto ArtificalGravity = -NewUpVelocity.Size() / DeltaTime*GetUpVector();
	//		//auto CorrectionForce = (TankRoot->GetMass()*ArtificalGravity) / 2;
	//		//TankRoot->AddForce(CorrectionForce);
	//	}

	//}

	//if (NewUpVelocity.Size() > MaxUpVelocity)
	//{
	//	NewUpVelocity = FVector(GetComponentVelocity().X, GetComponentVelocity().Y, -NewUpVelocity.Z);
	//	SetAllPhysicsLinearVelocity(NewUpVelocity,false);
	//	//SetAllPhysicsLinearVelocity
	//}
}

void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, +1);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

