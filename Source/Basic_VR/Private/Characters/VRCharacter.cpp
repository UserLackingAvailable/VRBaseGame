// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/VRCharacter.h"


AVRCharacter::AVRCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;

}


void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

