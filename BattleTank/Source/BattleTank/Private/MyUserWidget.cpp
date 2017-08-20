// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

void UMyUserWidget::SetAimPointReference(UImage * AimPoint)
{
	UCanvasPanelSlot* canvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(AimPoint);
	FVector2D AimPointPosition = canvasSlot->GetAnchors().Maximum;

	ATankPlayerController * OwningController = Cast<ATankPlayerController>(this->GetOwningPlayer());

	if (!OwningController)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Controller"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player Controller Found: %s"), *OwningController->GetName());
		OwningController->SetAimPointPosition(AimPointPosition);
	}


	//OwningController->SetAimPointPosition(AimPointPosition);
	
	//FVector2D screenPosition, viewportPosition;
	//USlateBlueprintLibrary::LocalToAbsolute()
	//USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(),canvasSlot->GetPosition())
	/*UE_LOG(LogTemp, Warning, TEXT("vector 2: %s"), *AimPointposition.ToString());*/
}

