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
		//pelotaMesh->SetPhysMaterialOverride(fisicaAsset.Object);
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
	if(jugadorTemp) jugadorTemp->hasBall = false;
	APlayerController* controllerPlayer = GetWorld()->GetFirstPlayerController();
	ASoccerPlayerController* soccerController = Cast<ASoccerPlayerController>(controllerPlayer);
	ASoccerPlayer* soccerPlayer = Cast<ASoccerPlayer>(other);
	if (jugadorTemp != nullptr && soccerController != nullptr && soccerPlayer->TeamEnum == ETeamEnum::TE_Buenos) {
		soccerController->UnPossess();
		jugadorTemp->isPossessed = false;
	}
	pelotaMesh->SetSimulatePhysics(false);
	AttachToActor(other, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("PelotaSocket")));
	
	//auto sarasa = (UStaticMeshComponent*)other->GetComponentByClass(UStaticMeshComponent::StaticClass());
	//AttachToComponent(sarasa, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("PelotaSocket")));

	
	soccerPlayer->hasBall = true;
	soccerPlayer->pelotaActor = me;
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