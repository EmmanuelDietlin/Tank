// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TankSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TANKSGAME_API UTankSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
	int UserIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
	int MaxScore;





	UTankSaveGame();
	
};
