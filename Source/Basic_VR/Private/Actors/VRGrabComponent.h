// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "VRGrabComponent.generated.h"

class UMotionControllerComponent;

UENUM(BlueprintType)
enum class EGrabType : uint8
{
	Free    UMETA(DisplayName = "Free Grab"),
	Snap    UMETA(DisplayName = "Snap to Socket")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UVRGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRGrabComponent();
	
	UPROPERTY(BlueprintReadOnly, Category = "Grab")
	TObjectPtr<class AVRhand> HoldingHand;

	UFUNCTION(BlueprintCallable, Category = "Grab")
	void TryGrab(class AVRhand* Hand);
	UFUNCTION(BlueprintCallable, Category = "Grab")
	void TryRelease();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grab Settings")
	EGrabType GrabType = EGrabType::Free;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grab Settings", meta = (EditCondition = "GrabType == EGrabType::Snap", EditConditionHides))
	FName R_SnapSocketName = TEXT("GripSocket_R");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grab Settings", meta = (EditCondition = "GrabType == EGrabType::Snap", EditConditionHides))
	FName L_SnapSocketName = TEXT("GripSocket_L");


		
};
