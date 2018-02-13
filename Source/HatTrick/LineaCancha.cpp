// Fill out your copyright notice in the Description page of Project Settings.

#include "LineaCancha.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Pelota.h"
#include "SoccerPlayer.h"
#include "SoccerPlayerController.h"
#include "HatTrickGameModeBase.h"
#include "EstadosEnum.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"


// Sets default values
ALineaCancha::ALineaCancha()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObj(TEXT("/Game/Mesh/linea"));
	UStaticMesh* linesMeshFbx = StaticMeshObj.Object;
	lineaMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Linea"));
	lineaMesh->SetStaticMesh(linesMeshFbx);
	lineaMesh->SetCollisionProfileName(TEXT("Linea"));
	lineaMesh->OnComponentBeginOverlap.AddDynamic(this, &ALineaCancha::OnOverlapBegin);
}

void ALineaCancha::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AHatTrickGameModeBase>(GetWorld()->GetAuthGameMode());
	//OnEstadoChange.AddDynamic(this, &ALineaCancha::RunDispatcherEstados);
}

void ALineaCancha::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APelota* laPelota = Cast<APelota>(OtherActor);
	if (laPelota == nullptr) return;
	pelotaInterseccionLinea = laPelota->GetActorLocation();
	switch (lateralEnum){
	case ELineaLateral::Lateral_Abajo:
		estado = EnumEstadosJuego::Saque_Lateral_Abajo;
		gameMode->OnEstadoChange.Broadcast(estado);
		salePelotaLateral(laPelota, pelotaInterseccionLinea);
		break;

	case ELineaLateral::Lateral_Arriba:
		estado = EnumEstadosJuego::Saque_Lateral_Arriba;
		gameMode->OnEstadoChange.Broadcast(estado);
		salePelotaLateral(laPelota, pelotaInterseccionLinea);
		break;
	
	case ELineaLateral::Fondo_Buenos:
		estado = EnumEstadosJuego::Saque_Arco;
		gameMode->OnEstadoChange.Broadcast(estado);
		break;
	case ELineaLateral::Fondo_Malos:
		estado = EnumEstadosJuego::Saque_Arco;
		gameMode->OnEstadoChange.Broadcast(estado);
		break;

	default:
		break;
	}
}

void ALineaCancha::PosicionarJugadorSaque(bool equipoBueno, APelota* pelota, ASoccerPlayer* player, FVector posicion)
{
	FVector posicionFinal = FVector(posicion.X, posicion.Y, 18);
	APlayerController* controllerPlayer = player->GetWorld()->GetFirstPlayerController();
	ASoccerPlayerController* soccerController = Cast<ASoccerPlayerController>(controllerPlayer);
	soccerController->checkChange(posicionFinal, equipoBueno, pelota);
}


void ALineaCancha::salePelotaLateral(APelota * laPelota, FVector pelotaInterseccionLinea)
{
	if (laPelota->jugadorTemp->TeamEnum == ETeamEnum::TE_Buenos) {
		//sacarian los malos que son false, porque lo tiro un bueno
		PosicionarJugadorSaque(false, laPelota, laPelota->jugadorTemp, pelotaInterseccionLinea);
	}
	else {
		//sacarian los buenos que son true
		PosicionarJugadorSaque(true, laPelota, laPelota->jugadorTemp, pelotaInterseccionLinea);
	}
}



