// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPlayer.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pelota.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "HatTrickGameModeBase.h"


// Sets default values
ASoccerPlayer::ASoccerPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ShootMontageObj(TEXT("/Game/Mesh/shot_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BarridaMontageObj(TEXT("/Game/Mesh/entrada_Montage"));
	ShootMontage = ShootMontageObj.Object;
	BarridaMontage = BarridaMontageObj.Object;
	
}

// Called when the game starts or when spawned
void ASoccerPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	gameMode = Cast<AHatTrickGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gameMode)
		gameMode->players.Add(this);
}

// Called every frame
void ASoccerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ASoccerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Girar", this, &ASoccerPlayer::girar);
	InputComponent->BindAxis("Adelante", this, &ASoccerPlayer::adelante);
	InputComponent->BindAction("Shot", IE_Pressed, this, &ASoccerPlayer::shot);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

}

void ASoccerPlayer::girar(float value)
{
	if (inAnimation) return;

	// add movement in that direction
	AddMovementInput(FVector(0,1,0), value);
}

void ASoccerPlayer::adelante(float value)
{
	if (inAnimation) return;

	AddMovementInput(FVector(1,0,0), value);
}

void ASoccerPlayer::shot()
{
	if (hasBall) {
		shotball = true;
		pelotaActor->DetachRootComponentFromParent(true);
		APelota* pelotaMaldita = Cast<APelota>(pelotaActor);
		pelotaMaldita->Physic(true);
		hasBall = false;
		PlayAnimMontage(ShootMontage, 1.0f);
		inAnimation = true;
		tiempoDelay = ShootMontage->GetPlayLength();
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenerico, tiempoDelay);

		//Magia del pase perfecto

		
		ASoccerPlayer* nearestPlayer = GetNearestPlayer();
		if (nearestPlayer) {
			locationPase = (nearestPlayer->GetActorLocation() - GetActorLocation())*fuerzaPase;
		}
		else {
			locationPase = GetActorForwardVector() * 1000;
		}

		//pelotaMaldita->Shootea(GetActorForwardVector(), 1000);
		pelotaMaldita->Shootea(locationPase);
	}
	else {
		PlayAnimMontage(BarridaMontage, 1.0f);
		inAnimation = true;
		tiempoDelay = BarridaMontage->GetPlayLength();
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenerico, tiempoDelay);
	}
}

void ASoccerPlayer::TimerGenerico()
{
	inAnimation = false;
}

void ASoccerPlayer::posesion()
{
	
}

ASoccerPlayer* ASoccerPlayer::GetNearestPlayer()
{
	ASoccerPlayer* nearestPlayer = nullptr;
	float nearestDot = -1;
	for (int i = 0; i < gameMode->players.Num(); i++)
	{
		ASoccerPlayer* player = gameMode->players[i];
		if (player == this) continue;

		//Obtengo la dirección desde yo hacia el jugador que estoy recorriendo
		FVector dirToPlayer = player->GetActorLocation() - GetActorLocation();
		dirToPlayer.Normalize();

		//Obtengo que tan paralelo es la direccion hacia el jugador y mi direccion hacia adelante
		//De esa forma puedo saber que tan paralelo a mi vision esta el jugador
		float dot = FVector::DotProduct(dirToPlayer, GetActorForwardVector());

		//Si encuentro un jugador cuyo dot es mejor que el mas cercano lo considero el nuevo mas cercano
		if (dot > nearestDot && dot > detectPlayerRange)
		{
			//Calculamos la distancia entre el jugador y yo y si esta dentro del rango de vision lo tengo en cuenta
			float dist = FVector::Distance(player->GetActorLocation(), GetActorLocation());
			if (dist <= detectPlayerDistance)
			{
				nearestPlayer = player;
				nearestDot = dot;
			}
		}		
	}
	return nearestPlayer;
}