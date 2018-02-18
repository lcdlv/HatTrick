// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"
#include "SoccerPlayer.h"
#include "PosicionPlayerSystem.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EnumPlayerPosiciones : uint8
{
	Arquero 				UMETA(DisplayName = "Arquero"),
	Defensa1			 	UMETA(DisplayName = "Defensa1"),
	Defensa2 				UMETA(DisplayName = "Defensa2"),
	Defensa3	 			UMETA(DisplayName = "Defensa3"),
	Defensa4 				UMETA(DisplayName = "Defensa4"),
	Mediocampo1 			UMETA(DisplayName = "Mediocampo1"),
	Mediocampo2 			UMETA(DisplayName = "Mediocampo2"),
	Mediocampo3 			UMETA(DisplayName = "Mediocampo3"),
	Mediocampo4 			UMETA(DisplayName = "Mediocampo4"),
	Mediocampo5 			UMETA(DisplayName = "Mediocampo5"),
	Ataque1 				UMETA(DisplayName = "Ataque1"),
	Ataque2 				UMETA(DisplayName = "Ataque2"),
	Ataque3 				UMETA(DisplayName = "Ataque3"),
	Ataque4 				UMETA(DisplayName = "Ataque4"),
};

UCLASS()
class HATTRICK_API APosicionPlayerSystem : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
	APlayerStart* ArqueroStart;

	UPROPERTY(EditAnywhere)
	APlayerStart* Defensa1Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Defensa2Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Defensa3Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Defensa4Start;
	
	UPROPERTY(EditAnywhere)
	APlayerStart* Mediocampo1Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Mediocampo2Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Mediocampo3Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Mediocampo4Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Mediocampo5Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Ataque1Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Ataque2Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Ataque3Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* Ataque4Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloArqueroStart;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloDefensa1Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloDefensa2Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloDefensa3Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloDefensa4Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloMediocampo1Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloMediocampo2Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloMediocampo3Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloMediocampo4Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloMediocampo5Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloAtaque1Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloAtaque2Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloAtaque3Start;

	UPROPERTY(EditAnywhere)
	APlayerStart* MaloAtaque4Start;

	UFUNCTION()
	FVector PlayerPosition(EnumPlayerPosiciones posicion, ETeamEnum equipo);

	FVector posicionStart;

	UPROPERTY(EditAnywhere)
	AActor* pelota;
};
