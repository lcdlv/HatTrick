// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerGoal.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EEquipoEnum : uint8
{
	TE_Buenos 	UMETA(DisplayName = "Buenos"),
	TE_Malos 	UMETA(DisplayName = "Malos"),
};

UCLASS()
class HATTRICK_API AMyTriggerGoal : public ATriggerBox
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyTriggerGoal();
	
	UFUNCTION()
	void OnBeginOverlap(class AActor* me, class AActor* other);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipo")
	EEquipoEnum TeamEnum;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class AHatTrickGameModeBase* gameMode;
};
