// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "TVCamera.generated.h"

/**
 * 
 */
UCLASS()
class HATTRICK_API ATVCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ATVCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APelota* pelota;
	
	FTimerHandle timerHander;

	void TimerGenerico();
};
