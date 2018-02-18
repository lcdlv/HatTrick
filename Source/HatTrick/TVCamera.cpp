// Fill out your copyright notice in the Description page of Project Settings.

#include "TVCamera.h"
#include "TimerManager.h"
#include "Pelota.h"
#include "Engine/World.h"

ATVCamera::ATVCamera() {

}

void ATVCamera::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(timerHander, this, &ATVCamera::TimerGenerico, 0.001, true);
}


void ATVCamera::TimerGenerico()
{
	if (pelota != nullptr) {
	SetActorLocation(FVector(pelota->GetActorLocation().X-500, pelota->GetActorLocation().Y, 360));
	}
}
