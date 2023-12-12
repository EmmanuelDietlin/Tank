// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LevelsData.h"
#include "MultiplayerData.h"
#include "TankGameInstance.generated.h"


UENUM(BlueprintType)
enum EMultiplayerVersusModeType 
{
	Timer UMETA(DisplayName = "Timer"),
	Lives UMETA(DisplayName = "Lives")
};

USTRUCT(BlueprintType)
struct FVersusGameData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EMultiplayerVersusModeType> VersusModeType;

	UPROPERTY(BlueprintReadWrite)
	int Lives;

	UPROPERTY(BlueprintReadWrite)
	int TimerSeconds;

	UPROPERTY(BlueprintReadWrite)
	float InvicibilityDuration;
};

USTRUCT(BlueprintType)
struct FVersusPlayerInfos 
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int Id;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	int Score;

	UPROPERTY(BlueprintReadWrite)
	int Lives;

};
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

	UPROPERTY(BlueprintReadWrite)
	int MaxLives = 4;

	UPROPERTY(BlueprintReadWrite)
	int LevelNumber = 0;

};
