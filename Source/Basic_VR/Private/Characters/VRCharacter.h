// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

UCLASS()
class AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AVRCharacter();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
