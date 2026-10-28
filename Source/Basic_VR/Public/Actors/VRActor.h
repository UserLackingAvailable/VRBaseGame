// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRActor.generated.h"

UCLASS()
class BASIC_VR_API AVRActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AVRActor();

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ActorMesh;

public:	


};
