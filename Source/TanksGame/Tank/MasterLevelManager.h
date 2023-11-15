// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "MasterLevelManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVictoryDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMainMenuDelegate);

UCLASS()
class TANKSGAME_API AMasterLevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterLevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void LoadNextLevel();
	UFUNCTION()
	void LoadCurrentLevel();
	UFUNCTION()
	void UnloadCurrentLevel();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void NextLevel();
	UFUNCTION(BlueprintCallable)
	void NextLevelWithDelay(float Delay);
	UFUNCTION(BlueprintCallable)
	void RestartLevel();
	UFUNCTION()
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
	int GetTanksCountForNextLevel();
	UFUNCTION(BlueprintCallable)
	bool IsLastLevel();

public:
	UPROPERTY(EditAnywhere, Category = "Levels")
	TArray<TSoftObjectPtr<UWorld>> OrderedLevelsList;

	UPROPERTY(BlueprintAssignable)
	FVictoryDelegate OnVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FMainMenuDelegate OnMainMenu;

private:
	int CurrentLevelIndex = -1;
	FTimerHandle TimerHandle;

};
