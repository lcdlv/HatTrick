// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoccerAIController.generated.h"

/**
 * 
 */
UCLASS()
class HATTRICK_API ASoccerAIController : public AAIController
{
	GENERATED_BODY()
	
virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	
private:
	class AHatTrickGameModeBase* gameMode;

public:
	// Sets default values for this pawn's properties
	ASoccerAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class ASoccerPlayer* player;
	
	UFUNCTION()
	void RunDispatcher(EnumEstadosJuego estado);

	FTimerHandle timerHander;

	void TimerGenerico();

	void MoverPersonaje();

	void Moverlocation(FVector lugar);

	bool volviendoPosicion = false;

};
