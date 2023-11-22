// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TankSaveGame.generated.h"


USTRUCT(BlueprintType)
struct FPlayerInfos 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxScore;
};

/**
 * 
 */
UCLASS()
class TANKSGAME_API UTankSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FPlayerInfos PlayerInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	int UserIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	float SoundVolume = 1 UMETA(ClampMin = "0", ClampMax = "1");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	float MusicVolume = 1 UMETA(ClampMin = "0", ClampMax = "1");

	UTankSaveGame();
	
};
