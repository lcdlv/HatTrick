﻿// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasBall = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool shotball = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* pelotaActor;

	UPROPERTY()
		UAnimMontage *MyCMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UShapeComponent* PieCollition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* RootMesh;

};
