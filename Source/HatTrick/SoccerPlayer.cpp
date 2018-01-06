// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPlayer.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pelota.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "TimerManager.h"


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
	// find out which way is right
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, value);
}

void ASoccerPlayer::adelante(float value)
{
	if (inAnimation) return;
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, value);
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
		pelotaMaldita->Shootea(GetActorForwardVector(), 1000);
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenerico, tiempoDelay);
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


