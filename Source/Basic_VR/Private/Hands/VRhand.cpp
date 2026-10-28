// Fill out your copyright notice in the Description page of Project Settings.


#include "Hands/VRhand.h"

#include "MotionControllerComponent.h"
#include "Actors/VRGrabComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"


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

	if (DeltaTime > 0.0f && MotionController)
	{
		FVector CurrentLocation = MotionController->GetComponentLocation();
		
		HandVelocity = (CurrentLocation - LastHandLocation) / DeltaTime;
		
		LastHandLocation = CurrentLocation;
	}
}

class UVRGrabComponent* AVRhand::GetNearestGrabComponent()
{
	if (!MotionController) return nullptr;
    
	FVector LocalGripPosition = MotionController->GetComponentLocation();
    
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));
    
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);               
	ActorsToIgnore.Add(GetOwner());         
    
	TArray<UPrimitiveComponent*> OverlappingComponents;
    
	bool bOverlap = UKismetSystemLibrary::SphereOverlapComponents(GetWorld(), LocalGripPosition, GrabRadius, ObjectTypes, nullptr, ActorsToIgnore, OverlappingComponents
	);
    
	//DrawDebugSphere(GetWorld(), LocalGripPosition, GrabRadius, 16, FColor::Red, false, 0.2f);
    
	if (!bOverlap || OverlappingComponents.Num() == 0)
	{
		return nullptr;
	}
    
	UVRGrabComponent* LocalNearestGrabComponent = nullptr;
	float LocalNearestComponentDistance = 999999.0f;
    
	for (UPrimitiveComponent* Comp : OverlappingComponents)
	{
		if (!Comp) continue;
        
		UVRGrabComponent* GrabComp = Comp->GetOwner()->FindComponentByClass<UVRGrabComponent>();
		if (!GrabComp) continue;
        
		float DistanceSquared = (GrabComp->GetComponentLocation() - LocalGripPosition).SizeSquared();
		if (DistanceSquared <= LocalNearestComponentDistance)
		{
			LocalNearestComponentDistance = DistanceSquared;
			LocalNearestGrabComponent = GrabComp;
		}
	}
    
	if (LocalNearestGrabComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("Hand (%s) near grabbable component: %s"), 
			(HandType == EControllerHand::Left) ? TEXT("Left") : TEXT("Right"), 
			*LocalNearestGrabComponent->GetName());
	}
    
	return LocalNearestGrabComponent;
}


