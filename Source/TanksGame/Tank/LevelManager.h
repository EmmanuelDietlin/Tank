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
	UFUNCTION(BlueprintCallable)
	void RestartLevel();

private:
	FTimerHandle ChangeLevelTimer;
	float LevelChangeTimer = 0;
	bool LevelEnded = false;
	FString CurrentLevel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UnloadCurrentLevel();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();

public:
	UPROPERTY(EditAnywhere, Category = "Enemies")
	TArray<TWeakObjectPtr<AEnemyTank>> EnemyTanks;

	UPROPERTY(EditAnywhere, Category = "Level", Meta = (EditCondition = "LevelStreamingEnabled == false", EditConditionHides))
	TSoftObjectPtr<UWorld> NextLevel;

	UPROPERTY(BlueprintAssignable)
	FVictoryDelegate OnVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FNextLevelDelegate OnNextLevelDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Level", Meta = (EditCondition = "LevelStreamingEnabled == false", EditConditionHides))
	bool IsLastLevel = false;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool SwitchLevelOnComplete = true;

	UPROPERTY(BlueprintReadonly)
	int RemainingTanks = 0;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Level")
	bool LevelStreamingEnabled = false;
};
