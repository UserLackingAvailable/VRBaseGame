// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Characters/VRCharacter.h"
#include "VRPlayerCharacter.generated.h"

//Forward Declares
class UMotionControllerComponent;
class UVRGrabComponent;
class AVRhand;

UCLASS()
class AVRPlayerCharacter : public AVRCharacter
{
	GENERATED_BODY()

public:
	AVRPlayerCharacter();
	
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")   //ctrl + shift + /  comments section out
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Origin")
	TObjectPtr<USceneComponent> Origin;
	
	UPROPERTY(EditDefaultsOnly, Category = "VR | Hands")
	TSubclassOf<class AVRhand> BPHand_L;
	
	UPROPERTY(EditDefaultsOnly, Category = "VR | Hands")
	TSubclassOf<class AVRhand> BPHand_R;
	
	UPROPERTY(VisibleAnywhere, Category = "VR | Hands")
	AVRhand* SpawnedHand_L;

	UPROPERTY(VisibleAnywhere, Category = "VR | Hands")
	AVRhand* SpawnedHand_R;
	
#pragma region Inputs
	
	void HandleMovement(const struct FInputActionValue& InputActionValue);
	void HandleTurn(const struct FInputActionValue& InputActionValue);
	
	void HandleGrab(EControllerHand InHandType);
	void HandleRelease(EControllerHand InHandType);
	void HandleToggleFlashlight(EControllerHand InHandType);
	
	void HandleLGrab(const struct FInputActionValue& InputActionValue);
	void HandleRGrab(const struct FInputActionValue& InputActionValue);
	void HandleLRelease(const struct FInputActionValue& InputActionValue);
	void HandleRRelease(const struct FInputActionValue& InputActionValue);
	void HandleLToggleFlashlight(const FInputActionValue& InputActionValue);
	void HandleRToggleFlashlight(const FInputActionValue& InputActionValue);
	
	
	FVector GetRightDirection() const;
	FVector GetMoveForwardDirection() const;
	FVector GetLookForwardDirection() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputMappingContext* GameplayMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputMappingContext* GameplayMappingContextHands;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* IAMove;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* IATurn;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* IAGrabPressed_L;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* IAGrabPressed_R;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* IAGrabReleased_L;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* IAGrabReleased_R;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* RToggleFlashlight;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* LToggleFlashlight;
	
#pragma endregion Inputs
	
};
