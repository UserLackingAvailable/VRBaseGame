// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/VRCharacter.h"
#include "Camera/CameraComponent.h"

AVRCharacter::AVRCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	Origin->SetupAttachment(GetMesh());
	
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(Origin);
	
}


void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

