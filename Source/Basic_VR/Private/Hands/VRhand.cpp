// Fill out your copyright notice in the Description page of Project Settings.


#include "Hands/VRhand.h"

#include "MotionControllerComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/SphereComponent.h"


//cpp needs to know the function so call the includes here

AVRhand::AVRhand()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>("MotionController");
	SetRootComponent(MotionController);
	
	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HandMesh");
	HandMesh->SetupAttachment(MotionController);
	
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>("WidgetInteraction");
	WidgetInteractionComponent->SetupAttachment(HandMesh);
	
	GrabSphere = CreateDefaultSubobject<USphereComponent>("GrabSphere");
	GrabSphere->SetupAttachment(HandMesh);
}

void AVRhand::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform); //super goes to parent class first and runs function

	switch (HandType)
	{
	case EControllerHand::Left:
		MotionController->MotionSource = "Left";
		break;
	case EControllerHand::Right:
		MotionController->MotionSource = "Right";
		break;
	default:
		break;
	}
}

void AVRhand::BeginPlay()
{
	Super::BeginPlay();
	
	if (HandType != EControllerHand::Left && HandType != EControllerHand::Right)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("Class %s: Wrong HandType"), *GetClass()->GetName()));
		}
	}
}

void AVRhand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

