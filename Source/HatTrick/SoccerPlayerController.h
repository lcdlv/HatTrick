// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SoccerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HATTRICK_API ASoccerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class AHatTrickGameModeBase* gameMode;

public:

	FTimerHandle timerHander;

	void TimerGenerico();
};
