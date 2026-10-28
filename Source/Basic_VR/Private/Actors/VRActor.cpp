// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VRActor.h"

// Sets default values
AVRActor::AVRActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(ActorMesh);

}


void AVRActor::BeginPlay()
{
	Super::BeginPlay();
	
}



