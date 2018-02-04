// Fill out your copyright notice in the Description page of Project Settings.

#include "Pelota.h"
#include "SoccerPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "SoccerPlayerController.h"


// Sets default values
APelota::APelota()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pelotaMesh = CreateDefaultSubobject<UStaticMeshComponent>("Shape");
	RootComponent = pelotaMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> shapeAsset(TEXT("/Game/Mesh/soccer_ball"));
	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> fisicaAsset(TEXT("/Game/Mesh/PelotaPhysicalMaterial"));
	pelotaMesh->SetStaticMesh(shapeAsset.Object);
	pelotaMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	pelotaMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	pelotaMesh->SetCollisionProfileName(FName("Pelota"));

	if (fisicaAsset.Succeeded()) {
		pelotaMesh->SetPhysMaterialOverride(fisicaAsset.Object);
	}
	pelotaMesh->SetSimulatePhysics(true);
	pelotaMesh->WakeRigidBody();
	

}

// Called when the game starts or when spawned
void APelota::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APelota::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &APelota::OnEndOverlap);

}

// Called every frame
void APelota::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APelota::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APelota::Physic(bool activado)
{
	pelotaMesh->SetSimulatePhysics(activado);
}

void APelota::Shootea(FVector vector)
{
	pelotaMesh->SetPhysicsLinearVelocity(vector);
}


void APelota::OnBeginOverlap(AActor * me, AActor * other)
{
	//si alguien la tenia antes, le saca el bool a hasball
	if(jugadorTemp) jugadorTemp->hasBall = false;
	//castea controller
	APlayerController* controllerPlayer = GetWorld()->GetFirstPlayerController();
	ASoccerPlayerController* soccerController = Cast<ASoccerPlayerController>(controllerPlayer);
	//castea el player con el que choca
	soccerPlayer = Cast<ASoccerPlayer>(other);
	//Si ovelapea con uno de los nuestros desposee el anterior y possee el nuevo. Sino, nunca lo desposee por lo que
	//seguimos usando el que estabamos usando.
	if (jugadorTemp != nullptr && soccerController != nullptr && soccerPlayer->TeamEnum == ETeamEnum::TE_Buenos) {
		soccerController->UnPossess();
		jugadorTemp->isPossessed = false;
	}
	pelotaMesh->SetSimulatePhysics(false);
	AttachToActor(other, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("PelotaSocket")));
	soccerPlayer->hasBall = true;
	soccerPlayer->pelotaActor = me;
	//Posee para manejar solo si choca con uno de los nuestros
	if (soccerPlayer->TeamEnum == ETeamEnum::TE_Buenos) {
		soccerController->Possess(soccerPlayer);
		soccerPlayer->isPossessed = true;
	}
	jugadorTemp = soccerPlayer;
}

void APelota::OnEndOverlap(AActor * me, AActor * other)
{
	ASoccerPlayer* player = Cast<ASoccerPlayer>(other);
	player->SinPelota();
}