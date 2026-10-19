// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRhand.generated.h"

//header only needs to know class exist not its function!!! (forward declaration)
class UMotionControllerComponent;
class USkeletalMeshComponent;
class UWidgetInteractionComponent;
class USphereComponent;

UCLASS()
class BASIC_VR_API AVRhand : public AActor
{
	GENERATED_BODY()
	
public:	
	AVRhand();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	//TObjectPtr same as * but handles objects better since UE made specifically for that for better optimization  (custom unreal pointer)
	
	//COMPONENTS//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UMotionControllerComponent> MotionController;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Hands")
	TObjectPtr<USkeletalMeshComponent> HandMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Hands")
	TObjectPtr<UWidgetInteractionComponent> WidgetInteractionComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Hands")
	TObjectPtr<USphereComponent> GrabSphere;
	
	//HAND DATA//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Hands|HandData")
	EControllerHand HandType;  //native enum which already takes small amount of memory so ptr isnt needed
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Hands|HandData")
	bool bMirrorAnimation;
private:

};
