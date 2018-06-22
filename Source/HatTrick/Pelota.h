// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pelota.generated.h"

UCLASS()
class HATTRICK_API APelota : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APelota();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class AHatTrickGameModeBase* gameMode;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* pelotaMesh;

	UPROPERTY(EditAnywhere)
	class ASoccerPlayer* jugadorTemp;

	void Physic(bool activado);

	void Shootea(FVector vector);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASoccerPlayer* soccerPlayer;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* me, AActor* other);

	UFUNCTION()
		void OnEndOverlap(AActor* me, AActor* other);

};
