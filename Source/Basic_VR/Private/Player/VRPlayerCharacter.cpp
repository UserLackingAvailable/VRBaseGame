// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VRPlayerCharacter.h"
#include "Actors/VRGrabComponent.h"
#include "MotionControllerComponent.h"
#include "Hands/VRhand.h"

#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "VRPlayerController.h"
#include "Actors/VRFlashlight.h"

AVRPlayerCharacter::AVRPlayerCharacter()
{
	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	Origin->SetupAttachment(GetMesh());
	
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(Origin);
	

}

void AVRPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetController<AVRPlayerController>()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
	if (EnhancedInputLocalPlayerSubsystem)
	{
		EnhancedInputLocalPlayerSubsystem->ClearAllMappings();
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(GameplayMappingContext, 0);
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(GameplayMappingContextHands, 0);
	}
}

void AVRPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &AVRPlayerCharacter::HandleMovement);
		EnhancedInputComponent->BindAction(IATurn, ETriggerEvent::Started, this, &AVRPlayerCharacter::HandleTurn);
		
		EnhancedInputComponent->BindAction(IAGrabPressed_L, ETriggerEvent::Triggered, this, &AVRPlayerCharacter::HandleLGrab);
		EnhancedInputComponent->BindAction(IAGrabPressed_R, ETriggerEvent::Triggered, this, &AVRPlayerCharacter::HandleRGrab);
		EnhancedInputComponent->BindAction(IAGrabReleased_L, ETriggerEvent::Completed, this, &AVRPlayerCharacter::HandleLRelease);
		EnhancedInputComponent->BindAction(IAGrabReleased_R, ETriggerEvent::Completed, this, &AVRPlayerCharacter::HandleRRelease);
		EnhancedInputComponent->BindAction(LToggleFlashlight, ETriggerEvent::Triggered, this, &AVRPlayerCharacter::HandleLToggleFlashlight);
		EnhancedInputComponent->BindAction(RToggleFlashlight, ETriggerEvent::Triggered, this, &AVRPlayerCharacter::HandleRToggleFlashlight);
		
	}
}

void AVRPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform SpawnTransform = FTransform::Identity;

	FAttachmentTransformRules AttachRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		true
	);

	//Spawn + Attach to Origin
	if (BPHand_L)
	{
		SpawnedHand_L = GetWorld()->SpawnActor<AVRhand>(BPHand_L, SpawnTransform, SpawnParams);
		if (SpawnedHand_L && Origin)
		{
			SpawnedHand_L->AttachToComponent(Origin, AttachRules);
		}
	}

	
	if (BPHand_R)
	{
		SpawnedHand_R = GetWorld()->SpawnActor<AVRhand>(BPHand_R, SpawnTransform, SpawnParams);
		if (SpawnedHand_R && Origin)
		{
			SpawnedHand_R->AttachToComponent(Origin, AttachRules);
		}
	}
}

void AVRPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AVRPlayerCharacter::GetRightDirection() const
{
	return Camera->GetRightVector();
}

FVector AVRPlayerCharacter::GetMoveForwardDirection() const
{
	return FVector::CrossProduct(GetRightDirection(), FVector::UpVector);
}

FVector AVRPlayerCharacter::GetLookForwardDirection() const
{
	return Camera->GetForwardVector();
}


void AVRPlayerCharacter::HandleMovement(const struct FInputActionValue& InputActionValue)
{
	FVector2D InputAction = InputActionValue.Get<FVector2D>();
	/*InputAction.Normalize();*/
	
	
	AddMovementInput(GetMoveForwardDirection() * InputAction.Y + GetRightDirection() * InputAction.X);
}

void AVRPlayerCharacter::HandleTurn(const struct FInputActionValue& InputActionValue)
{
	FVector2D TurnValue = InputActionValue.Get<FVector2D>();
	float SnapAngle = 15.0f;

	float Direction = (TurnValue.X > 0.0f) ? 1.0f : -1.0f;
	
	if (Controller)
	{
		FRotator NewRotation = Controller->GetControlRotation();
		NewRotation.Yaw += (SnapAngle * Direction);
		Controller->SetControlRotation(NewRotation);
	}
}

void AVRPlayerCharacter::HandleGrab(EControllerHand InHandType)
{
	UE_LOG(LogTemp, Log, TEXT("TryGrab button pressed for hand type: %d"), (int32)InHandType);
	
	AVRhand* TargetHand = (InHandType == EControllerHand::Left) ? SpawnedHand_L : SpawnedHand_R;
	if (!TargetHand)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grab failed: TargetHand is null!"));
		return;
	}
	
	UVRGrabComponent* FoundGrabbable = TargetHand->GetNearestGrabComponent();
	
	if (FoundGrabbable)
	{
		UE_LOG(LogTemp, Warning, TEXT("GRAB SUCCESS!")); 
		
		FoundGrabbable->TryGrab(TargetHand);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GRAB FAILED, NO GRABBABLE CLOSE ENOUGH!")); 
	}
}

void AVRPlayerCharacter::HandleRelease(EControllerHand InHandType)
{
	AVRhand* TargetHand = (InHandType == EControllerHand::Left) ? SpawnedHand_L : SpawnedHand_R;
	if (!TargetHand) return;
	
	UVRGrabComponent* FoundGrabComp = TargetHand->GetNearestGrabComponent();
	if (TargetHand->HeldComponent)
	{
		TargetHand->HeldComponent->TryRelease();
		TargetHand->HeldComponent = nullptr; // Clear it
	}
}

void AVRPlayerCharacter::HandleLGrab(const struct FInputActionValue& InputActionValue)
{
	HandleGrab(EControllerHand::Left);
}

void AVRPlayerCharacter::HandleRGrab(const struct FInputActionValue& InputActionValue)
{
	HandleGrab(EControllerHand::Right);
}

void AVRPlayerCharacter::HandleLRelease(const struct FInputActionValue& InputActionValue)
{
	HandleRelease(EControllerHand::Left);
}

void AVRPlayerCharacter::HandleRRelease(const struct FInputActionValue& InputActionValue)
{
	HandleRelease(EControllerHand::Right);
}

void AVRPlayerCharacter::HandleLToggleFlashlight(const FInputActionValue& InputActionValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Left Flashlight Button Pressed!"));
	HandleToggleFlashlight(EControllerHand::Left);
}

void AVRPlayerCharacter::HandleRToggleFlashlight(const FInputActionValue& InputActionValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, TEXT("Right Flashlight Button Pressed!"));
	HandleToggleFlashlight(EControllerHand::Right);
}

void AVRPlayerCharacter::HandleToggleFlashlight(EControllerHand InHandType)
{
	AVRhand* TargetHand = (InHandType == EControllerHand::Left) ? SpawnedHand_L : SpawnedHand_R;
	if (!TargetHand) return;

	
	if (TargetHand->HeldComponent)
	{
		AActor* HeldActor = TargetHand->HeldComponent->GetOwner();
		if (AVRFlashlight* Flashlight = Cast<AVRFlashlight>(HeldActor))
		{
			Flashlight->Interact();
		}
	}
}
