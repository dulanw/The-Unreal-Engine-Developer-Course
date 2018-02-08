// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable)
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, int MinToSpawn = 1, int MaxToSpawn = 1, int Radius = 500, float MinScale = 1.f, float MaxScale = 1.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool isEmptyLocation(FVector &OUTSpawnLocation,float Radius);
	void  PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector SpawnLocation, float SpawnRotation, float SpawnScale);
	bool CanSpawnAtLocation(FVector Location, float Radius);
	
};
