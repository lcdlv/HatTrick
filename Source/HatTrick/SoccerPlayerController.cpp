// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPlayerController.h"
#include "HatTrickGameModeBase.h"
#include "TimerManager.h"
#include "SoccerPlayer.h"



void ASoccerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AHatTrickGameModeBase>(GetWorld()->GetAuthGameMode());
	GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayerController::TimerGenerico, 2);
}



void ASoccerPlayerController::TimerGenerico()
{
	gameMode->checkChange(FVector(10, 1080, 0));
}
