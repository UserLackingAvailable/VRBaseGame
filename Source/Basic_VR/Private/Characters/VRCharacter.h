// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

class UCameraComponent;

UCLASS()
class AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AVRCharacter();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer() const;
	
	virtual void PossessedBy(AController* NewController) override;

protected:
	
	virtual void BeginPlay() override;

};
