// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimPlayer.generated.h"

/**
*
*/
UCLASS()
class HATTRICK_API UAnimPlayer : public UAnimInstance
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool HasBall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Velocidad;

};

