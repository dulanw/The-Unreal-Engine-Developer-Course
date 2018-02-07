// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

class ATank;
class UImage;

/**
 * 
 */

UCLASS()
class BATTLETANK_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable)
		void SetAimPointReference(UImage* AimPoint);

};
