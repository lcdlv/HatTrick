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

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EnumPlayerPosicionesLocal : uint8
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

	void btnShotRelease();

	void btnPaseRelease();

	void btnShotPress();

	void btnPasePress();

	void btnChange();

	void TimerGenericoEmpuja();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasBall = false;

	UPROPERTY(EditAnywhere)
		bool shotball = false;

	UPROPERTY(EditAnywhere)
		bool inAnimation = false;

	UPROPERTY(EditAnywhere)
		bool inEmpuja = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class APelota* pelotaActor;

	UPROPERTY()
		UAnimMontage *ShootMontage;

	UPROPERTY()
		UAnimMontage *BarridaMontage;

	UPROPERTY()
		UAnimMontage *CaeMontage;

	UPROPERTY()
		UAnimMontage *PaseMontage;


	UPROPERTY()
		UAnimMontage *EmpujonMontage;

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
		float detectPlayerRange = 0.6;

	UPROPERTY(EditAnywhere)
		FVector locationPase = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere)
		ASoccerPlayer* playerTemp;

	int fuerzaPase = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soccer Player")
	ETeamEnum TeamEnum;

	void SinPelota();

	void esGolpeado();

	int pressed = 0;

	bool isPress = false;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool isPossessed;

	int fuerza();

	UPROPERTY(EditAnywhere)
	UMaterialInterface* materialBueno;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* materialMalo;

	UPROPERTY(EditAnywhere)
	EnumPlayerPosicionesLocal PosicionCancha = EnumPlayerPosicionesLocal::Arquero;

	UPROPERTY(EditAnywhere)
	class APosicionPlayerSystem* posicionActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector posicionDefault;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* ArcoObjetivo;

	bool NotMovement = true;

	class ASoccerAIController* AIPlayerController;

	//bool capsulaIAOverlap = false;

	FVector estrategiaAtaque = FVector(0, 500, 0);
	
	UFUNCTION()
		void RunDispatcherEstrategia(ETeamEnum equipo);
};

