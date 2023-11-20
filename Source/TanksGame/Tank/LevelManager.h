// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTank.h"
#include "TankSaveGame.h"
#include "LevelsData.h"
#include "Camera/CameraActor.h"
#include "Engine/EngineTypes.h"
#include "MasterLevelManager.h"
#include "PlayerTank.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNextLevelDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseDelegate, bool, Pause);

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
	AMasterLevelManager* MasterLevelManager = nullptr;
	APlayerTank* Player = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();
	UFUNCTION(BlueprintCallable)
	void TogglePause(bool Pause);
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();

public:
	UPROPERTY(EditAnywhere, Category = "Enemies")
	TArray<TWeakObjectPtr<AEnemyTank>> EnemyTanks;

	UPROPERTY(EditAnywhere, Category = "Level", Meta = (EditCondition = "LevelStreamingEnabled == false", EditConditionHides))
	TSoftObjectPtr<UWorld> NextLevel;

	UPROPERTY(EditAnywhere, Category = "Level", Meta = (EditCondition = "LevelStreamingEnabled == false", EditConditionHides))
	TSoftObjectPtr<UWorld> MainMenu;
	
	UPROPERTY(BlueprintAssignable)
	FVictoryDelegate OnVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FNextLevelDelegate OnNextLevelDelegate;

	UPROPERTY()
	FPauseDelegate OnPauseDelegate;

	UPROPERTY(EditAnywhere, Category = "Level")
	ULevelsData* LevelsData;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Level", Meta = (EditCondition = "LevelStreamingEnabled == false", EditConditionHides))
	bool IsLastLevel = false;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool SwitchLevelOnComplete = true;

	UPROPERTY(BlueprintReadonly)
	int RemainingTanks = 0;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Level")
	bool LevelStreamingEnabled = false;
};
