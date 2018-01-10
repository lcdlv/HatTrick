// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "SoccerPlayer.generated.h"

UCLASS()
class HATTRICK_API ASoccerPlayer : public ACharacter
{
	GENERATED_BODY()

private:
	class AHatTrickGameModeBase* gameMode;
	class ASoccerPlayer* GetNearestPlayer();
public:
	// Sets default values for this pawn's properties
	ASoccerPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void girar(float value);

	void adelante(float value);

	void shot();

	void TimerGenerico();

	void posesion();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasBall = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool shotball = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool inAnimation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* pelotaActor;

	UPROPERTY()
		UAnimMontage *ShootMontage;

	UPROPERTY()
		UAnimMontage *BarridaMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UShapeComponent* PieCollition;

	FTimerHandle timerHander;

	UPROPERTY(EditAnywhere)
	float tiempoDelay;

	UPROPERTY(EditAnywhere)
	float detectPlayerDistance = 1000;

	UPROPERTY(EditAnywhere)
	float detectPlayerRange = 0.75;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* RootMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector locationPase = FVector(0,0,0);

	int fuerzaPase = 3;
};

