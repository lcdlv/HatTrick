// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoccerPlayer.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETeamEnum : uint8
{
	TE_Buenos 	UMETA(DisplayName = "Buenos"),
	TE_Malos 	UMETA(DisplayName = "Malos"),
};

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

	void TimerGenericoEmpuja();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasBall = false;

	UPROPERTY(EditAnywhere)
	bool shotball = false;

	UPROPERTY(EditAnywhere)
	bool inAnimation = false;

	UPROPERTY(EditAnywhere)
	bool inEmpuja = false;

	UPROPERTY(EditAnywhere)
	AActor* pelotaActor;

	UPROPERTY()
	UAnimMontage *ShootMontage;

	UPROPERTY()
	UAnimMontage *BarridaMontage;

	UPROPERTY()
	UAnimMontage* GolpeadoMontage;

	FTimerHandle timerHander;

	UPROPERTY(EditAnywhere)
	float tiempoDelay;

	UPROPERTY(EditAnywhere)
	float detectPlayerDistance = 1000;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* capsulaCustom;

	UPROPERTY(EditAnywhere)
	float detectPlayerRange = 0.75;

	UPROPERTY(EditAnywhere)
	FVector locationPase = FVector(0,0,0);
	
	UPROPERTY(EditAnywhere)
	ASoccerPlayer* playerTemp;

	int fuerzaPase = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soccer Player")
	ETeamEnum TeamEnum;
	
	void SinPelota();

	void esGolpeado();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

