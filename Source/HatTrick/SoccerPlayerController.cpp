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

	//Esto hace que sea solo Single Player ya que siempre serias de los buenos.
	for (int i = 0; i < gameMode->playersBuenos.Num(); i++)
	{
		ASoccerPlayer* player = gameMode->playersBuenos[i];

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
	Possess(nearestPlayer);
	nearestPlayer->isPossessed = true;
}

void ASoccerPlayerController::checkChange(FVector posicionSaque, bool playerBueno, APelota* pelota) {

	ASoccerPlayer* nearestPlayer = nullptr;
	float distTemp = 10000000;

		if (playerBueno) {
			UE_LOG(LogTemp, Warning, TEXT("El que la tiro afuera es Malo, un Bueno Saca"));
			for (int i = 0; i < gameMode->playersBuenos.Num(); i++)
			{
				ASoccerPlayer* player = gameMode->playersBuenos[i];

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
			Possess(nearestPlayer);
			nearestPlayer->isPossessed = true;
			nearestPlayer->SetActorLocation(posicionSaque);
			pelota->AttachToActor(nearestPlayer, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("PelotaSocket")));
		}
		else {
			for (int i = 0; i < gameMode->playersMalos.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("El que la tiro afuera es Bueno, un Malo Saca"));
				ASoccerPlayer* player = gameMode->playersMalos[i];

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
			pelota->AttachToActor(nearestPlayer, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("PelotaSocket")));
		}
}
