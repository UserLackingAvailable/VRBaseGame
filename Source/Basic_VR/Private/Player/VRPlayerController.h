// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VRPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AVRPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* NewPawn) override;
	
	virtual void AcknowledgePossession(APawn* NewPawn) override;
	
private:
	UPROPERTY()
	class AVRPlayerCharacter* VRPlayerCharacter;
};
