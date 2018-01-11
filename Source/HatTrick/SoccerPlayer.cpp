// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPlayer.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pelota.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "HatTrickGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ASoccerPlayer::ASoccerPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ShootMontageObj(TEXT("/Game/Mesh/shot_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BarridaMontageObj(TEXT("/Game/Mesh/entrada_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GolpeadoMontageObj(TEXT("/Game/Mesh/cambio_sentido_Montage"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletoObj(TEXT("/Game/Mesh/player"));
	static ConstructorHelpers::FObjectFinder<UClass> animationBlueprint(TEXT("/Game/MyAnimPlayer.MyAnimPlayer_C"));

	ShootMontage = ShootMontageObj.Object;
	BarridaMontage = BarridaMontageObj.Object;
	GolpeadoMontage = GolpeadoMontageObj.Object;
	capsulaCustom = CreateAbstractDefaultSubobject<UCapsuleComponent>(TEXT("CapsulaColicion"));
	capsulaCustom->InitCapsuleSize(40.f, 88.0f);
	capsulaCustom->SetCollisionProfileName(FName("Jugador"));
	capsulaCustom->SetupAttachment(RootComponent);
	capsulaCustom->OnComponentBeginOverlap.AddDynamic(this, &ASoccerPlayer::OnOverlapBegin);
	GetMesh()->SetSkeletalMesh(SkeletoObj.Object, false);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(animationBlueprint.Object);
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
}

// Called when the game starts or when spawned
void ASoccerPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	
	gameMode = Cast<AHatTrickGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gameMode) {
		switch (TeamEnum) {
			case ETeamEnum::TE_Buenos: {
				gameMode->playersBuenos.Add(this);
			}
			case ETeamEnum::TE_Malos: {
				gameMode->playersMalos.Add(this);
			}
		}	
	}
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
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenericoEmpuja, tiempoDelay);

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
		if (playerTemp != nullptr) playerTemp->esGolpeado();
		inAnimation = true;
		inEmpuja = true;
		tiempoDelay = BarridaMontage->GetPlayLength();
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenericoEmpuja, tiempoDelay);
	}
}

void ASoccerPlayer::TimerGenericoEmpuja()
{
	inAnimation = false;
	inEmpuja = false;
}


ASoccerPlayer* ASoccerPlayer::GetNearestPlayer()
{
	ASoccerPlayer* nearestPlayer = nullptr;
	float nearestDot = -1;

	switch (TeamEnum) {
	case ETeamEnum::TE_Buenos: {
		for (int i = 0; i < gameMode->playersBuenos.Num(); i++)
		{
			ASoccerPlayer* player = gameMode->playersBuenos[i];
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
	case ETeamEnum::TE_Malos: {
		for (int i = 0; i < gameMode->playersMalos.Num(); i++)
		{
			ASoccerPlayer* player = gameMode->playersMalos[i];
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
}

	
	return nearestPlayer;
}


void ASoccerPlayer::SinPelota()
{
		StopAnimMontage(GetCurrentMontage());
		GetCharacterMovement()->Velocity = FVector(0,0,0);
		hasBall = false;
}

void ASoccerPlayer::esGolpeado()
{
	PlayAnimMontage(ShootMontage, 1.0f);
	inAnimation = true;
	tiempoDelay = ShootMontage->GetPlayLength();
	GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenericoEmpuja, tiempoDelay);
}

void ASoccerPlayer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Verga"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
		playerTemp = Cast<ASoccerPlayer>(OtherActor);

	}
}






