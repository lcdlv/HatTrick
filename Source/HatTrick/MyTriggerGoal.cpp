// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTriggerGoal.h"
#include "HatTrickGameModeBase.h"
#include "Engine/World.h"

AMyTriggerGoal::AMyTriggerGoal()
{
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerGoal::OnBeginOverlap);
}


void AMyTriggerGoal::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<AHatTrickGameModeBase>(GetWorld()->GetAuthGameMode());
}

void AMyTriggerGoal::OnBeginOverlap(AActor * me, AActor * other)
{
	switch (TeamEnum) {
		case EEquipoEnum::TE_Buenos: {
			gameMode->GolBuenos++;
			UE_LOG(LogTemp, Warning, TEXT("Gol Buenos is %d"), gameMode->GolBuenos);
			break;
		}
		case EEquipoEnum::TE_Malos: {
			gameMode->GolMalos++;
			UE_LOG(LogTemp, Warning, TEXT("Gol Malos is %d"), gameMode->GolMalos);
			break;
		}
	}
	
}