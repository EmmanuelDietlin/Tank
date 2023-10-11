// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TankGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TANKSGAME_API UTankGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int Score = 0;
	
};