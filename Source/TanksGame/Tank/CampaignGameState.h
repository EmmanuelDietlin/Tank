// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CampaignGameState.generated.h"

/**
 * 
 */
UCLASS()
class TANKSGAME_API ACampaignGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int Score;

	UPROPERTY(BlueprintReadWrite)
	int Lives;

	UPROPERTY(BlueprintReadWrite)
	int RemainingEnemyTanks;
	
	UPROPERTY(BlueprintReadWrite)
	int LevelNumber;
	
};
