// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VRFlashlight.h"
#include "Components/SpotLightComponent.h"
// Sets default values
AVRFlashlight::AVRFlashlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Flashlight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashlightMesh"));
	SetRootComponent(SM_Flashlight);
	
	FlashlightLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashlightLight"));
	FlashlightLight->SetupAttachment(SM_Flashlight);
	
	bIsOn = true;
}

void AVRFlashlight::Interact()
{
	bIsOn = !bIsOn;
	if (FlashlightLight)
	{
		FlashlightLight->SetVisibility(bIsOn);
	}
}

// Called when the game starts or when spawned
void AVRFlashlight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

