// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mine.h"
#include "Engine/DataAsset.h"
#include "MinesData.generated.h"

/**
 * 
 */
UENUM()
enum MineTypes {
	PlayerMine UMETA(DisplayName = "PlayerMine"),
	EnemyStandadMine UMETA(DisplayName = "EnemyStandardMine"),
};

USTRUCT()
struct FMineData 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Mine")
	float MineExplosionDelay = 5;

	UPROPERTY(EditAnywhere, Category = "Mine")
	float MineExplosionRadius = 100;

	UPROPERTY(EditAnywhere, Category = "Mine")
	TSubclassOf<AMine> Mine;
};

UCLASS()
class TANKSGAME_API UMinesData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Mines")
	TMap<TEnumAsByte<MineTypes>, FMineData> Mines;
	
};
