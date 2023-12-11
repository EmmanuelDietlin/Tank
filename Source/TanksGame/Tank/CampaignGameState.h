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
	UPROPERTY(BlueprintReadWrite, Replicated)
	int Score;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int Lives;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int RemainingEnemyTanks;
	
	UPROPERTY(BlueprintReadWrite, Replicated)
	int LevelNumber;
};
