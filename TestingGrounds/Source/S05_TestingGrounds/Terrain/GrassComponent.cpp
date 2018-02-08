// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"

void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnGrass();
}

void UGrassComponent::SpawnGrass()
{
	FVector MinimumBound(0, -2000, 0);
	FVector MaximumBound(4000, 2000, 0);
	FBox BoxBound = FBox(MinimumBound, MaximumBound);

	for (int32 i = 0; i < SpawnCount; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(BoxBound);
		AddInstance(FTransform(SpawnLocation));
	}
	
}
