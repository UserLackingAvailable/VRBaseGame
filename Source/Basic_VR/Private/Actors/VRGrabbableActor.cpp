// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VRGrabbableActor.h"


#include "Components/BoxComponent.h"

AVRGrabbableActor::AVRGrabbableActor()
{
	GrabRegion = CreateDefaultSubobject<UBoxComponent>("GrabBoxRegion");
	GrabRegion->SetupAttachment(ActorMesh);
	
	GrabRegion->SetCollisionProfileName("Grabbable");
}
