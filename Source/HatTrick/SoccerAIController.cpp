// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerAIController.h"
#include "Engine/World.h"
#include "SoccerPlayer.h"
#include "EstadosEnum.h"
#include "TimerManager.h"
#include "HatTrickGameModeBase.h"

ASoccerAIController::ASoccerAIController() {

}

void ASoccerAIController::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AHatTrickGameModeBase>(GetWorld()->GetAuthGameMode());
	player = Cast<ASoccerPlayer>(GetCharacter());
	gameMode->OnEstadoChange.AddDynamic(this, &ASoccerAIController::RunDispatcher);
}

void ASoccerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASoccerAIController::RunDispatcher(EnumEstadosJuego estado)
{
	switch (estado)
	{

	case EnumEstadosJuego::Falta:
		break;
	case EnumEstadosJuego::Goal:
		UE_LOG(LogTemp, Warning, TEXT("GOL!"));
		break;
	case EnumEstadosJuego::InGame:
		break;
	case EnumEstadosJuego::Penal:
		break;
	case EnumEstadosJuego::Saque_Arco:
		break;
	case EnumEstadosJuego::Saque_Falta:
		break;
	case EnumEstadosJuego::Saque_Lateral_Abajo:
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerAIController::TimerGenerico, 2);
		break;
	case EnumEstadosJuego::Saque_Lateral_Arriba:
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerAIController::TimerGenerico, 2);
		break;
	default:
		break;
	}
}

void ASoccerAIController::TimerGenerico()
{
	if (player->isPossessed) {
		player->btnPaseRelease();
		UE_LOG(LogTemp, Warning, TEXT("2 segundos"));
		gameMode->OnEstadoChange.Broadcast(EnumEstadosJuego::InGame);
	}
}
