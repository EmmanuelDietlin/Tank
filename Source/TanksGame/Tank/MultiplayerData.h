// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MultiplayerData.generated.h"


UENUM(BlueprintType)
enum EMapType 
{
	CoopMapType UMETA(DisplayName = "CoopMapType"),
	VersusMapType UMETA(DisplayName = "VersusMapType")
};

USTRUCT(BlueprintType)
struct FMapData 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TSoftObjectPtr<UWorld> Map;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FText LevelDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	int MaxPlayerNumber = 2;
};

/**
 * 
 */
UCLASS(BlueprintType)
class TANKSGAME_API UMultiplayerData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Maps")
	TArray<FMapData> CoopMapsList;

	UPROPERTY(EditAnywhere, Category = "Maps")
	TArray<FMapData> VersusMapsList;

public:
	UFUNCTION(BlueprintCallable)
	FMapData GetMapData(EMapType MapType, int Index);

	UFUNCTION(BlueprintCallable)
	int GetMapListSize(EMapType MapType);
	
};
