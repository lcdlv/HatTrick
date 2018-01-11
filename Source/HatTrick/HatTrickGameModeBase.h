// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HatTrickGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HATTRICK_API AHatTrickGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	TArray<class ASoccerPlayer*> playersBuenos;
	TArray<class ASoccerPlayer*> playersMalos;
	
	
};
