// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTank.h"
#include "TankSaveGame.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVictoryDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNextLevelDelegate);

UCLASS()
class TANKSGAME_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

private:
	FTimerHandle ChangeLevelTimer;
	float LevelChangeTimer = 0;
	bool LevelEnded = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Enemies")
	TArray<TWeakObjectPtr<AEnemyTank>> EnemyTanks;

	UPROPERTY(EditAnywhere, Category = "Next Level")
	TSoftObjectPtr<UWorld> NextLevel;

	UPROPERTY(BlueprintAssignable)
	FVictoryDelegate OnVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FNextLevelDelegate OnNextLevelDelegate;

	UPROPERTY(EditAnywhere, Category = "Next Level")
	bool IsLastLevel = false;

	UPROPERTY(EditAnywhere, Category = "Next Level")
	float NextLevelTimer = 2;
};
