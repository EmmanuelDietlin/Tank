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

	UPROPERTY(BlueprintReadWrite)
	int LevelScore = 0;

	UPROPERTY(BlueprintReadWrite)
	float SoundVolume = 0;

	UPROPERTY(BlueprintReadWrite)
	float MusicVolume = 0;

	UPROPERTY(BlueprintReadWrite)
	int Lives = 4;

	UPROPERTY(BlueprintReadonly)
	int MaxLives = 4;

	UPROPERTY(BlueprintReadWrite)
	int LevelNumber = 1;
	
};
