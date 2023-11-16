// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelsData.generated.h"


USTRUCT()
struct FLevelData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int TanksCount;
};

/**
 * 
 */
UCLASS()
class TANKSGAME_API ULevelsData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<TSoftObjectPtr<UWorld>, FLevelData> LevelsData;
	

public:
	void SetDataForLevel(FString LevelName, int value);
	FLevelData GetDataForLevel(FString LevelName);
};
