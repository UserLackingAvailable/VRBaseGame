// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VRGrabComponent.h"
#include "Hands/VRhand.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SkeletalMeshComponent.h"


UVRGrabComponent::UVRGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UVRGrabComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UVRGrabComponent::TryGrab(AVRhand* Hand)
{
	if (!Hand) return;
	if (Hand->HeldComponent) return;
	HoldingHand = Hand;
	Hand->HeldComponent = this;

	AActor* OwnerActor = GetOwner();
	if (!OwnerActor) return;
	
	if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(OwnerActor->GetRootComponent()))
	{
		RootPrim->SetSimulatePhysics(false);
		RootPrim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}


	if (GrabType == EGrabType::Free)
	{
		//Free
		OwnerActor->AttachToComponent(
		   Hand->GetRootComponent(), 
		   FAttachmentTransformRules::KeepWorldTransform
		);

	}
	else if (GrabType == EGrabType::Snap)
	{
		// Snap to socket
		if (Hand->HandMesh)
		{
			FName TargetSocket = (Hand->HandType == EControllerHand::Right) ? R_SnapSocketName : L_SnapSocketName;
			OwnerActor->AttachToComponent(Hand->HandMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TargetSocket);
		}
		else
		{
			
			OwnerActor->AttachToComponent(Hand->GetRootComponent(),FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}

void UVRGrabComponent::TryRelease()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor) return;

		if (HoldingHand)
		{
			if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(OwnerActor->GetRootComponent()))
			{
				RootPrim->SetSimulatePhysics(true);
				RootPrim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				RootPrim->SetPhysicsLinearVelocity(HoldingHand->GetHandVelocity());
			}
		}
	
	OwnerActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	HoldingHand = nullptr;

}

