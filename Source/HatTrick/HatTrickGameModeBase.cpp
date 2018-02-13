// Fill out your copyright notice in the Description page of Project Settings.

#include "HatTrickGameModeBase.h"
#include "EstadosEnum.h"
#include "SoccerPlayerController.h"


AHatTrickGameModeBase::AHatTrickGameModeBase()
{
	OnEstadoChange.AddDynamic(this, &AHatTrickGameModeBase::RunDispatcherEstados);
}

void AHatTrickGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	OnEstadoChange.Broadcast(estadoGame);
}



void AHatTrickGameModeBase::RunDispatcherEstados(EnumEstadosJuego estado)
{
	//UE_LOG(LogTemp, Warning, TEXT("Estado %d"), estado);
	estadoGame = estado;
}
