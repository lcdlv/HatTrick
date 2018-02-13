// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * 
 */

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EnumEstadosJuego : uint8
{
	Saque_Arco 				UMETA(DisplayName = "Saque de Arco"),
	Saque_Lateral_Abajo 	UMETA(DisplayName = "Lateral Abajo"),
	Saque_Lateral_Arriba 	UMETA(DisplayName = "Lateral Arriba"),
	Saque_Falta 			UMETA(DisplayName = "Saque Falta"),
	Falta 					UMETA(DisplayName = "Falta"),
	Penal 					UMETA(DisplayName = "Penal"),
	InGame 					UMETA(DisplayName = "In-Game"),
	Goal 					UMETA(DisplayName = "Gol"),
};

class HATTRICK_API EstadosEnum
{
public:
	EstadosEnum();
	~EstadosEnum();
};
