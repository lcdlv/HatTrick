// Fill out your copyright notice in the Description page of Project Settings.

#include "HatTrickGameModeBase.h"
#include "Pelota.h"
#include "SoccerPlayerController.h"
#include "SoccerPlayer.h"


AHatTrickGameModeBase::AHatTrickGameModeBase()
{
	OnEstadoChange.AddDynamic(this, &AHatTrickGameModeBase::RunDispatcherEstados);
}

void AHatTrickGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	OnEstadoChange.Broadcast(estadoGame);
	controllerPlayer = GetWorld()->GetFirstPlayerController();
	soccerController = Cast<ASoccerPlayerController>(controllerPlayer);
}



void AHatTrickGameModeBase::RunDispatcherEstados(EnumEstadosJuego estado)
{
	//UE_LOG(LogTemp, Warning, TEXT("Estado %d"), estado);
	estadoGame = estado;
}

void AHatTrickGameModeBase::checkChange(APelota* pelota) {

	ASoccerPlayer* nearestPlayer = nullptr;
	float distTemp = 10000000;

	//Esto hace que sea solo Single Player ya que siempre serias de los buenos.
	for (int i = 0; i < playersBuenos.Num(); i++)
	{
		ASoccerPlayer* player = playersBuenos[i];

		float dist = FVector::Distance(player->GetActorLocation(), pelota->GetActorLocation());
		if (dist <= distTemp)
		{
			nearestPlayer = player;
			distTemp = dist;
		}
		else {
			player->isPossessed = false;
			player->SinPelota();
		}
	}
	soccerController->Possess(nearestPlayer);
	nearestPlayer->isPossessed = true;
}

void AHatTrickGameModeBase::checkChange(FVector lugar) {

	ASoccerPlayer* nearestPlayer = nullptr;
	float distTemp = 10000000;

	//Esto hace que sea solo Single Player ya que siempre serias de los buenos.
	for (int i = 0; i < playersBuenos.Num(); i++)
	{
		ASoccerPlayer* player = playersBuenos[i];

		float dist = FVector::Distance(player->GetActorLocation(), lugar);
		if (dist <= distTemp)
		{
			nearestPlayer = player;
			distTemp = dist;
		}
		else {
			player->isPossessed = false;
			player->SinPelota();
		}
	}
	soccerController->Possess(nearestPlayer);
	nearestPlayer->isPossessed = true;
}

void AHatTrickGameModeBase::checkChange(FVector posicionSaque, bool playerBueno, APelota* pelota, EnumEstadosJuego estadoGame) {

	ASoccerPlayer* nearestPlayer = nullptr;
	float distTemp = 10000000;
	if (playerBueno) {
		UE_LOG(LogTemp, Warning, TEXT("1 El que la tiro afuera es Malo, un Bueno Saca"));
		for (int i = 0; i < playersBuenos.Num(); i++)
		{
			ASoccerPlayer* player = playersBuenos[i];

			float dist = FVector::Distance(player->GetActorLocation(), posicionSaque);
			if (dist <= distTemp)
			{
				nearestPlayer = player;
				distTemp = dist;
			}
			else {
				player->isPossessed = false;
				player->SinPelota();
			}
		}
		//Posee y hubica al personaje
		soccerController->Possess(nearestPlayer);
		nearestPlayer->isPossessed = true;
		nearestPlayer->SetActorLocation(posicionSaque);
		pelota->AttachToActor(nearestPlayer, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("PelotaSocket")));

		switch (estadoGame) {
		case EnumEstadosJuego::Saque_Lateral_Abajo:
			nearestPlayer->SetActorRotation(FRotator(0, 0, 0));
			UE_LOG(LogTemp, Warning, TEXT("ABAJO Acomoda"));
			break;
		case EnumEstadosJuego::Saque_Lateral_Arriba:
			nearestPlayer->SetActorRotation(FRotator(0, 180, 0));
			UE_LOG(LogTemp, Warning, TEXT("ARRIBA ACOMODA"));
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("BREAK"));
			break;
		}

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("2 El que la tiro afuera es Bueno, un Malo Saca"));
		for (int i = 0; i < playersMalos.Num(); i++)
		{
			ASoccerPlayer* player = playersMalos[i];

			float dist = FVector::Distance(player->GetActorLocation(), posicionSaque);
			if (dist <= distTemp)
			{
				nearestPlayer = player;
				distTemp = dist;
			}
			else {
				player->isPossessed = false;
				player->SinPelota();
			}
		}
		//Aca deberia posserlo la maquina...
		
		nearestPlayer->SetActorLocation(posicionSaque);
		nearestPlayer->isPossessed = true;
		pelota->AttachToActor(nearestPlayer, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("PelotaSocket")));
		switch (estadoGame) {
		case EnumEstadosJuego::Saque_Lateral_Abajo:
			nearestPlayer->SetActorRotation(FRotator(0, 0, 0));
			UE_LOG(LogTemp, Warning, TEXT("FALSE ABAJO Acomoda"));
			break;
		case EnumEstadosJuego::Saque_Lateral_Arriba:
			nearestPlayer->SetActorRotation(FRotator(0, 180, 0));
			UE_LOG(LogTemp, Warning, TEXT("FALSE ARRIBA ACOMODA"));
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("FALSE BREAK"));
			break;
		}
	}
}