// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPlayer.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pelota.h"
#include "SoccerPlayerController.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "HatTrickGameModeBase.h"
#include "PosicionPlayerSystem.h"
#include "Components/CapsuleComponent.h"
#include "SoccerAIController.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ASoccerPlayer::ASoccerPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Busca todos los montajes y cosas en las carpetas.
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ShootMontageObj(TEXT("/Game/Mesh/shot_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BarridaMontageObj(TEXT("/Game/Mesh/entrada_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GolpeadoMontageObj(TEXT("/Game/Mesh/cambio_sentido_Montage"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletoObj(TEXT("/Game/Mesh/player"));
	static ConstructorHelpers::FObjectFinder<UClass> animationBlueprint(TEXT("/Game/MyAnimPlayer.MyAnimPlayer_C"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialBuenoObj(TEXT("/Game/Mesh/Matblanco"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialMaloObj(TEXT("/Game/Mesh/Matnegro"));

	//transforma lo que encontro en su respectivo tipo de objeto
	materialBueno = MaterialBuenoObj.Object;
	materialMalo = MaterialMaloObj.Object;
	ShootMontage = ShootMontageObj.Object;
	BarridaMontage = BarridaMontageObj.Object;
	GolpeadoMontage = GolpeadoMontageObj.Object;
	//Crea capsula comun para pelota
	capsulaCustom = CreateAbstractDefaultSubobject<UCapsuleComponent>(TEXT("CapsulaColicion"));
	capsulaCustom->InitCapsuleSize(40.f, 88.0f);
	capsulaCustom->SetCollisionProfileName(FName("Jugador"));
	capsulaCustom->SetupAttachment(RootComponent);
	capsulaCustom->OnComponentBeginOverlap.AddDynamic(this, &ASoccerPlayer::OnOverlapBegin);
	capsulaCustom->OnComponentEndOverlap.AddDynamic(this, &ASoccerPlayer::OnOverlapEnd);
	//Tunea Mesh
	GetMesh()->SetSkeletalMesh(SkeletoObj.Object, false);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(animationBlueprint.Object);
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	//Crea capsula para deteccion de enemigos
	capsulaIA = CreateAbstractDefaultSubobject<UCapsuleComponent>(TEXT("CapsulaIA"));
	capsulaIA->InitCapsuleSize(300.f, 300.0f);
	capsulaIA->SetCollisionProfileName(FName("VePelota"));
	capsulaIA->SetupAttachment(RootComponent);
	capsulaIA->OnComponentBeginOverlap.AddDynamic(this, &ASoccerPlayer::OnOverlapIABegin);
	capsulaIA->OnComponentEndOverlap.AddDynamic(this, &ASoccerPlayer::OnOverlapIAEnd);
}

// Called when the game starts or when spawned
void ASoccerPlayer::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<AHatTrickGameModeBase>(GetWorld()->GetAuthGameMode());
	//Chequea en que equipo esta
	if (gameMode) {
		switch (TeamEnum) {
			case ETeamEnum::TE_Buenos: {
				//lo agrega a los buenos
				gameMode->playersBuenos.Add(this);
				//Le pone textura
				GetMesh()->SetMaterial(0, materialBueno);
				break;
			}
			case ETeamEnum::TE_Malos: {
				gameMode->playersMalos.Add(this);
				GetMesh()->SetMaterial(0, materialMalo);
				//Chequea si tiene un IA Controller asignado
				AIPlayerController = Cast<ASoccerAIController>(GetController());
				if (AIPlayerController) {
					//Llega aca si funciono.
				}
				break;
			}
		}	
	}

	//Chequea la posicion en la cancha, hace que vayan ahi y de paso la asigna como default position.
	switch (PosicionCancha)
	{
	case EnumPlayerPosicionesLocal::Arquero:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Arquero, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Arquero, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Defensa1:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Defensa1, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Defensa1, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Defensa2:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Defensa2, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Defensa2, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Defensa3:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Defensa3, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Defensa3, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Defensa4:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Defensa4, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Defensa4, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Mediocampo1:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo1, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo1, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Mediocampo2:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo2, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo2, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Mediocampo3:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo3, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo3, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Mediocampo4:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo4, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo4, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Mediocampo5:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo5, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Mediocampo5, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Ataque1:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Ataque1, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Ataque1, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Ataque2:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Ataque2, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Ataque2, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Ataque3:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Ataque3, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Ataque3, TeamEnum);
		break;
	case EnumPlayerPosicionesLocal::Ataque4:
		SetActorLocation(posicionActor->PlayerPosition(EnumPlayerPosiciones::Ataque4, TeamEnum));
		posicionDefault = posicionActor->PlayerPosition(EnumPlayerPosiciones::Ataque4, TeamEnum);
		break;
	}

	gameMode->OnEstrategiaChange.AddDynamic(this, &ASoccerPlayer::RunDispatcherEstrategia);
}

// Called every frame
void ASoccerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//chequea el press del boton para la fuerza.
	if (isPress) {
		pressed++;
		UE_LOG(LogTemp, Warning, TEXT("Energia is %d"), pressed);
	}
	else {
		pressed = 0;
	}

	// hace que siempre mire a la pelota. Tambien hace que se posea el player si esta cerca
	//El NOTMOVEMENT es en caso que este buscando al otro, se pone FALSE por lo que no entra
	// y no hace esto de buscar con la mirada al otro
	if (!hasBall && pelotaActor && !isPossessed && !inAnimation && NotMovement){

		FVector diferencia = (pelotaActor->GetActorLocation()) - GetActorLocation();
		diferencia.Normalize();
		FRotator rotacion = FRotator(0, diferencia.Rotation().Yaw, 0);
		
		//Sistema de osicalamiento continuo
		/*if (FVector::PointsAreNear((pelotaActor->GetActorLocation()), GetActorLocation(), 110)) {
			if (NotMovement || !capsulaIAOverlap) {
				UE_LOG(LogTemp, Warning, TEXT("Updatea"));
				capsulaIAOverlap = true;
				AIPlayerController->MoverPersonaje();
			}
			
		}*/
		//si no osicalo, rota.
		SetActorRotation(rotacion);

	}
}

// Called to bind functionality to input
void ASoccerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Carga los inputs
	InputComponent->BindAxis("Girar", this, &ASoccerPlayer::girar);
	InputComponent->BindAxis("Adelante", this, &ASoccerPlayer::adelante);
	InputComponent->BindAction("Pase", IE_Pressed, this, &ASoccerPlayer::btnPasePress);
	InputComponent->BindAction("Shot", IE_Pressed, this, &ASoccerPlayer::btnShotPress);
	InputComponent->BindAction("Pase", IE_Released, this, &ASoccerPlayer::btnPaseRelease);
	InputComponent->BindAction("Shot", IE_Released, this, &ASoccerPlayer::btnShotRelease);
	InputComponent->BindAction("Change", IE_Pressed, this, &ASoccerPlayer::btnChange);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

}

void ASoccerPlayer::btnChange()
{
	if (!hasBall) {
		//Si no tengo la pelota y no es NULL pelota, hago que el game mode busque otro jugador
		if (pelotaActor != nullptr) {
			gameMode->checkChange(pelotaActor);
		}
	}
	
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

void ASoccerPlayer::btnShotRelease()
{
	//hago que corte la sumatoria de fuerza
	isPress = false;

	//Si tengo la pelota suelto la pelota, le doy fisica, pongo que no la tengo mas, 
	// hago la animacion del disparo y aviso que estoy animando.
	//Tambien ejecuta el timer para que solo se ponga que ya no esta en una animacion ni bien termine la misma.
	if (hasBall) {
		shotball = true;
		pelotaActor->DetachRootComponentFromParent(true);
		pelotaActor->Physic(true);
		hasBall = false;
		inAnimation = true;
		PlayAnimMontage(ShootMontage, 1.0f);
		tiempoDelay = ShootMontage->GetPlayLength();
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenericoEmpuja, tiempoDelay);
		pelotaActor->Shootea(GetActorForwardVector()*fuerza()*1000);
	}
	else {
		//No hace nada aun. Es en caso de no tener la pelota
		//Deberia hacer el salto con patada voladora
	}
}

void ASoccerPlayer::btnPaseRelease()
{
	//saca el press asi deja de sumar fuerza
	isPress = false;
	//Hace el disparo buscando el personaje mas cercano.
	if (hasBall) {
		shotball = true;
		pelotaActor->DetachRootComponentFromParent(true);
		pelotaActor->Physic(true);
		hasBall = false;
		inAnimation = true;
		PlayAnimMontage(ShootMontage, 1.0f);
		tiempoDelay = ShootMontage->GetPlayLength();
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenericoEmpuja, tiempoDelay);

		//Magia del pase perfecto
		ASoccerPlayer* nearestPlayer = GetNearestPlayer();
		if (nearestPlayer) {
			locationPase = (nearestPlayer->GetActorLocation() - GetActorLocation())*fuerza();
		}
		else {
			locationPase = GetActorForwardVector() * (fuerza()*500);
		}
		pelotaActor->Shootea(locationPase);
	}
	else {

		//En caso que no tenga la pelota hace la barrida para sacarla.
		inAnimation = true;
		PlayAnimMontage(BarridaMontage, 1.0f);
		//Hace que el player enemigo sufra el golpe.
		inEmpuja = true;
		if (playerTemp != nullptr) playerTemp->esGolpeado();
		tiempoDelay = BarridaMontage->GetPlayLength();
		GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenericoEmpuja, tiempoDelay);
	}

}

void ASoccerPlayer::btnShotPress()
{
	//Activa para que se sume la fuerza.
	isPress = true;
}

void ASoccerPlayer::btnPasePress()
{
	//Activa para que se sume la fuerza
	isPress = true;
}

void ASoccerPlayer::TimerGenericoEmpuja()
{
	//Desabilita las variables ya que termino la animacion y la animacion de empuje
	inAnimation = false;
	inEmpuja = false;
}


//Magia de buscar el player mas cercano
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
	//Cuando no tengo la pelota freno montajes, y freno la carrera
		StopAnimMontage(GetCurrentMontage());
		hasBall = false;
		GetCharacterMovement()->Velocity = FVector(0,0,0);
	
}

void ASoccerPlayer::esGolpeado()
{
	//Me pegan, por ahora hace la animacion de patear. El timer hace que se salgan la variables.
	inAnimation = true;
	PlayAnimMontage(ShootMontage, 1.0f);
	tiempoDelay = ShootMontage->GetPlayLength();
	GetWorldTimerManager().SetTimer(timerHander, this, &ASoccerPlayer::TimerGenericoEmpuja, tiempoDelay);
}

void ASoccerPlayer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//Agarra al player con el que colisiono y lo manda a Temp, asi despues puedo pegarle.
		playerTemp = Cast<ASoccerPlayer>(OtherActor);

	}
}

void ASoccerPlayer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//Limpio el player de colision.
		playerTemp = nullptr;
	}
}

void ASoccerPlayer::OnOverlapIABegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (TeamEnum == ETeamEnum::TE_Malos && AIPlayerController && !hasBall && pelotaActor->jugadorTemp->TeamEnum != ETeamEnum::TE_Malos) {
		
		if (NotMovement) {
			UE_LOG(LogTemp, Warning, TEXT("BeginIA"));
			//La idea de esta variable es que cuando este true. Es un recoveco para saber mientras esta en colision.
			capsulaIAOverlap = true;
			AIPlayerController->MoverPersonaje();
		}
	}
}

void ASoccerPlayer::OnOverlapIAEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (TeamEnum == ETeamEnum::TE_Malos && AIPlayerController && !hasBall && pelotaActor->jugadorTemp->TeamEnum != ETeamEnum::TE_Malos) {
		
		if (NotMovement) {
			UE_LOG(LogTemp, Warning, TEXT("EndIA"));
			NotMovement = false;
			capsulaIAOverlap = false;
			//Hace que vuelva a la posicion default de ese momento.
			AIPlayerController->Moverlocation(posicionDefault);
		}
		
	}
}


//Deacuerdo a cuanto llego con la carga larga el golpe.
int ASoccerPlayer::fuerza()
{
	if (pressed <= 8) fuerzaPase = 2;
	if (pressed >= 9 && pressed <= 15) fuerzaPase = 3;
	if (pressed >= 16) fuerzaPase = 4;
	return fuerzaPase;
}

void ASoccerPlayer::RunDispatcherEstrategia(ETeamEnum equipo)
{
	if (equipo == TeamEnum && pelotaActor->jugadorTemp->TeamEnum != TeamEnum) {
		//Si es mi equipo paso al ataque
		
		switch (TeamEnum) {
			case ETeamEnum::TE_Buenos: {
				//Pasa al ataque el equipo Bueno
				UE_LOG(LogTemp, Warning, TEXT("Pasa al ataque los Buenos"));
				posicionDefault = posicionDefault + estrategiaAtaque;
				break;
			}
			case ETeamEnum::TE_Malos: {
				//Pasa al ataque el equipo Malo
				UE_LOG(LogTemp, Warning, TEXT("Pasa al ataque los Malo"));
				posicionDefault = posicionDefault - estrategiaAtaque;
				break;
			}
		}
		
		if (AIPlayerController && NotMovement) {
			NotMovement = false;
			capsulaIAOverlap = false;
			//Hace que vuelva a la posicion default de ese momento.
			AIPlayerController->Moverlocation(posicionDefault);
		}
	}
	if (equipo != TeamEnum && pelotaActor->jugadorTemp->TeamEnum == TeamEnum) {
		//No soy yo, por lo que paso a defensa
				switch (TeamEnum) {
				case ETeamEnum::TE_Buenos: {
					//Pasa al defensa el equipo Bueno
					UE_LOG(LogTemp, Warning, TEXT("Pasa a defensa los Buenos"));
					posicionDefault = posicionDefault - estrategiaAtaque;
					break;
				}
				case ETeamEnum::TE_Malos: {
					//Pasa al defensa el equipo Malos
					UE_LOG(LogTemp, Warning, TEXT("Pasa a defensa los Malos"));
					posicionDefault = posicionDefault + estrategiaAtaque;
					break;
				}
				}

				if (AIPlayerController && NotMovement) {
					NotMovement = false;
					capsulaIAOverlap = false;
					//Hace que vuelva a la posicion default de ese momento.
					AIPlayerController->Moverlocation(posicionDefault);
				}
		
	}
}








