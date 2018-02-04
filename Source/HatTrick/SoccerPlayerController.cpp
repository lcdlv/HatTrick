// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPlayerController.h"
#include "HatTrickGameModeBase.h"
#include "Engine/World.h"
#include "Pelota.h"
#include "SoccerPlayer.h"



void ASoccerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AHatTrickGameModeBase>(GetWorld()->GetAuthGameMode());
}

void ASoccerPlayerController::checkChange(APelota* pelota) {

	ASoccerPlayer* nearestPlayer = nullptr;
	float distTemp = 10000000;

	for (int i = 0; i < gameMode->playersBuenos.Num(); i++)
	{
		ASoccerPlayer* player = gameMode->playersBuenos[i];

		float dist = FVector::Distance(player->GetActorLocation(), pelota->GetActorLocation());
		if (dist <= distTemp)
		{
			nearestPlayer = player;
			distTemp = dist;
		}
	}
	nearestPlayer->PossessedBy(this);
}
