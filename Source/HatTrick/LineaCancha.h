// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LineaCancha.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ELineaLateral : uint8
{
	Lateral_Arriba 	UMETA(DisplayName = "Lateral Arriba"),
	Lateral_Abajo 	UMETA(DisplayName = "Lateral Abajo"),
	Fondo_Buenos 	UMETA(DisplayName = "Fondo Buenos"),
	Fondo_Malos 	UMETA(DisplayName = "Fondo Malos"),
};

UCLASS()
class HATTRICK_API ALineaCancha : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALineaCancha();

public:	

	UStaticMeshComponent* lineaMesh;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PosicionarJugadorSaque(bool equipoBueno, class APelota* pelota, class ASoccerPlayer* player, FVector posicion);

	FVector pelotaInterseccionLinea;

	UPROPERTY(EditAnywhere)
	ELineaLateral lateralEnum;
};
