// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRFlashlight.generated.h"

UCLASS()
class AVRFlashlight : public AActor
{
	GENERATED_BODY()
	
public:	
	AVRFlashlight();
	void Interact();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpotLightComponent* FlashlightLight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* SM_Flashlight;
	
	
	bool bIsOn = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
