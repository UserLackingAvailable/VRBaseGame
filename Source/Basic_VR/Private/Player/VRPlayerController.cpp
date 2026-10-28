// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VRPlayerController.h"
#include "Player/VRPlayerCharacter.h"

void AVRPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	
	VRPlayerCharacter = Cast<AVRPlayerCharacter>(NewPawn);
	if (VRPlayerCharacter)
	{
		VRPlayerCharacter->ServerSideInit();
	}
}

void AVRPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);
	VRPlayerCharacter = Cast<AVRPlayerCharacter>(NewPawn);
	if (VRPlayerCharacter)
	{
		//VRPlayerCharacter->ClientSideInit();
	}
}
