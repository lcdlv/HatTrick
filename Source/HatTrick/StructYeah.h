// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructYeah.generated.h"

USTRUCT(BlueprintType)
struct FJoyStruct
{
	GENERATED_USTRUCT_BODY()
		//Always make USTRUCT variables into UPROPERTY()
		//    any non-UPROPERTY() struct vars are not replicated

		// So to simplify your life for later debugging, always use UPROPERTY()
		UPROPERTY()
		int32 SampleInt32;

	//If you want the property to appear in BP, make sure to use this instead
	//UPROPERTY(BlueprintReadOnly)
	UPROPERTY()
		float TargetActor;

	/*Set
	void SetInt(const int32 NewValue, AActor* vergon)
	{
		SampleInt32 = NewValue;
		TargetActor = vergon;
	}

	//Get
	AActor* GetActor()
	{
		return TargetActor;
	}

	//Check
	bool ActorIsValid() const
	{
		if (!TargetActor) return false;
		return TargetActor->IsValidLowLevel();
	}
	
	//Constructor
	FJoyStruct()
	{
		//Always initialize your USTRUCT variables!
		//   exception is if you know the variable type has its own default constructor
		SampleInt32 = 5;
		TargetActor = NULL;
	}*/
};

