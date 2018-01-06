// Fill out your copyright notice in the Description page of Project Settings.

#include "Pelota.h"
#include "SoccerPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


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
		UE_LOG(LogTemp, Warning, TEXT("Entro"));
	}
	pelotaMesh->SetSimulatePhysics(true);
	pelotaMesh->WakeRigidBody();
	

}

// Called when the game starts or when spawned
void APelota::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APelota::OnOverlap);

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

void APelota::Shootea(FVector vector, float velocidadShot)
{
	pelotaMesh->SetPhysicsLinearVelocity(vector * velocidadShot);
}


void APelota::OnOverlap(AActor * me, AActor * other)
{
	if(jugadorTemp != nullptr) jugadorTemp->UnPossessed();
	pelotaMesh->SetSimulatePhysics(false);
	AttachToActor(other, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("PelotaSocket")));
	UE_LOG(LogTemp, Warning, TEXT("Toca"));
	ASoccerPlayer* soccerPlayer = Cast<ASoccerPlayer>(other);
	soccerPlayer->hasBall = true;
	soccerPlayer->pelotaActor = me;
	soccerPlayer->posesion();
	jugadorTemp = soccerPlayer;
}
