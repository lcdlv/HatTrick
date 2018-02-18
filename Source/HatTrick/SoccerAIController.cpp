// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerAIController.h"
#include "Engine/World.h"
#include "SoccerPlayer.h"
#include "EstadosEnum.h"
#include "TimerManager.h"
#include "Pelota.h"
#include "PosicionPlayerSystem.h"
#include "Components/CapsuleComponent.h"
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

void ASoccerAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	if (volviendoPosicion) {
		//Hace que vuelva a mirar estando parado
		player->NotMovement = true;
		//Ya no esta volviendo
		volviendoPosicion = false;
	}
	
	
	
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
		break;
	case EnumEstadosJuego::InGame:
		Moverlocation(player->posicionDefault);
		break;
	case EnumEstadosJuego::Penal:
		break;
	case EnumEstadosJuego::Saque_Arco:
		break;
	case EnumEstadosJuego::Saque_Falta:
		break;
	case EnumEstadosJuego::Saque_Lateral_Abajo:
		StopMovement();
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerAIController::TimerGenerico, 2);
		break;
	case EnumEstadosJuego::Saque_Lateral_Arriba:
		StopMovement();
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerAIController::TimerGenerico, 2);
		break;
	default:
		break;
	}
}

void ASoccerAIController::TimerGenerico()
{
	if (player->isPossessed) {
		//Patea
		player->btnPaseRelease();
		//Avisa que vuelve a Ingame
		gameMode->OnEstadoChange.Broadcast(EnumEstadosJuego::InGame);
	}
}

void ASoccerAIController::MoverPersonaje()
{	
		//Va a un actor
		MoveToActor(player->posicionActor->pelota);
}

void ASoccerAIController::Moverlocation(FVector lugar)
{
	//Se frena
	StopMovement();
	//Ve donde esta el default position
	FVector loc = lugar - player->GetActorLocation();
	loc.Normalize();
	FRotator rotacion = FRotator(0, loc.Rotation().Yaw, 0);
	//Hace la rotacion hacia ese lado
	player->SetActorRotation(rotacion);
	//Activa que esta volviendo
	volviendoPosicion = true;
	MoveToLocation(lugar);
	GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerAIController::TimerVuelve, 1, true);
}

void ASoccerAIController::TimerVuelve()
{
		//Si ya no vuelve, y la capsula dice que esta con overlap, sale a buscar la pelota.
		if (!volviendoPosicion && player->capsulaIAOverlap) {
			UE_LOG(LogTemp, Warning, TEXT("Activa el buscado"));
			MoverPersonaje();
		}
}
