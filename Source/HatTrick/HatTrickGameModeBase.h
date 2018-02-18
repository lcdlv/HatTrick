// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EstadosEnum.h"
#include "SoccerPlayer.h"
#include "HatTrickGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEstadoDispatcher, EnumEstadosJuego, EstadoGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEstrategiaDispatcher, ETeamEnum, EstrategiaGame);

UCLASS()
class HATTRICK_API AHatTrickGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	TArray<class ASoccerPlayer*> playersBuenos;
	TArray<class ASoccerPlayer*> playersMalos;
	
	AHatTrickGameModeBase();

	UPROPERTY(EditAnywhere)
	int GolBuenos = 0;

	UPROPERTY(EditAnywhere)
	int GolMalos = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EnumEstadosJuego estadoGame = EnumEstadosJuego::InGame;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatcher")
	FEstadoDispatcher OnEstadoChange;

	UFUNCTION()
	void RunDispatcherEstados(EnumEstadosJuego estado);

	void checkChange(class APelota* pelota);

	void checkChange(FVector posicionSaque, bool playerBueno, class APelota* pelota, EnumEstadosJuego estadoGame);

	void checkChange(FVector lugar);

	UPROPERTY(EditAnywhere)
	float detectPlayerRange = 0.6;

	class APlayerController* controllerPlayer;

	class ASoccerPlayerController* soccerController;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatcher")
	FEstrategiaDispatcher OnEstrategiaChange;


};
