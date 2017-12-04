// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int MinToSpawn, int MaxToSpawn, int Radius, float MinScale, float MaxScale)
{
	//FVector MinimumBound(0, -2000, 0);
	//FVector MaximumBound(4000, 2000, 0);
	//FBox BoxBounds(MinimumBound, MaximumBound);
	//int NumberToSpawn = FMath::RandRange(MinToSpawn, MaxToSpawn);
	//for (size_t i = 0; i < NumberToSpawn; i++)
	//{
	//	FVector SpawnPoint = FMath::RandPointInBox(BoxBounds);
	//	UE_LOG(LogTemp, Warning, TEXT("SpawnPoint is: %s"), *SpawnPoint.ToString());
	//	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
	//	SpawnedActor->SetActorRelativeLocation(SpawnPoint);
	//	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
	//}

	int NumberToSpawn = FMath::RandRange(MinToSpawn, MaxToSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnLocation;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		if (isEmptyLocation(SpawnLocation, Radius * RandomScale))
		{
			float RandomRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ActorToSpawn, SpawnLocation, RandomRotation, RandomScale);
		}
		//UE_LOG(LogTemp, Warning, TEXT("SpawnPoint is: %s"), *SpawnPoint.ToString());
	}	
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::isEmptyLocation(FVector &OUTSpawnLocation, float Radius)
{
	FVector MinimumBound(0, -2000, 0);
	FVector MaximumBound(4000, 2000, 0);
	FBox BoxBounds(MinimumBound, MaximumBound);
	for (int32 i = 0; i < 100; i++)
	{
		FVector EmptyLocation = FMath::RandPointInBox(BoxBounds);
		if (CanSpawnAtLocation(EmptyLocation, Radius))
		{
			OUTSpawnLocation = EmptyLocation;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector SpawnLocation, float SpawnRotation, float SpawnScale)
{
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
		SpawnedActor->SetActorRelativeLocation(SpawnLocation);
		SpawnedActor->SetActorRelativeRotation(FRotator(0, SpawnRotation, 0));
		SpawnedActor->SetActorRelativeScale3D(FVector(SpawnScale));
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = GetTransform().TransformPosition(Location);
	bool bHasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	FColor ResultColour = bHasHit ? FColor::Red : FColor::Green;

	//DrawDebugSphere(GetWorld(), Location, Radius, 32, ResultColour, true, 100);
	//DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColour, true, 100);
	return !bHasHit;
}

