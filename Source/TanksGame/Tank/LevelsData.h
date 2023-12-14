// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelsData.generated.h"


USTRUCT(BlueprintType)
struct FLevelData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	int TanksCount;
};

/**
 * 
 */
UCLASS(BlueprintType)
class TANKSGAME_API ULevelsData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TArray<FLevelData> LevelsData;
	

public:
	void SetDataForLevel(FString LevelName, int value);
	FLevelData GetDataForLevel(FString LevelName);
	UFUNCTION(BlueprintCallable)
	int GetLevelIndex(FString LevelName);
};
