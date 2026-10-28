// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/VRCharacter.h"
/*#include "GameFramework/CharacterMovementComponent.h"*/

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

void AVRCharacter::ServerSideInit()
{
	//server called
}

void AVRCharacter::ClientSideInit()
{
	//client called
}

bool AVRCharacter::IsLocallyControlledByPlayer() const
{
	return IsLocallyControlled() && GetController()->IsPlayerController();
}

void AVRCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}
}

