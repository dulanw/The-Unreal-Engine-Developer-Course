// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "../Weapons/Gun.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(0.44f, -5.25f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	//Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if (!GunBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GunBlueprint!"));
		return;
	}

	FPWeapon = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	TPWeapon = GetWorld()->SpawnActor<AGun>(GunBlueprint);

	FPWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true), TEXT("GripPoint"));
	TPWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));

	FPWeapon->SetOwningPawn(this);
	TPWeapon->SetOwningPawn(this);

	FPWeapon->SetIsFirstPerson(true);
	TPWeapon->SetIsFirstPerson(false);
	
	FPWeapon->FPAnimInstance = Mesh1P->GetAnimInstance();
	FPWeapon->TPAnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMannequin::PullTrigger()
{
	if (!FPWeapon || !TPWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Gun Attached to player, Cannot fire!"));
		return;
	}
	
	FPWeapon->TriggerPulled();
	TPWeapon->TriggerPulled();
}

void AMannequin::ReleaseTrigger()
{
	if (!FPWeapon || !TPWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Gun Attached to player, Cannot fire!"));
		return;
	}
	FPWeapon->TriggerReleased();
	TPWeapon->TriggerReleased();
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMannequin::ReleaseTrigger);
}

