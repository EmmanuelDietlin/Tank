// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "LevelManager.h"
#include "GameFramework/Actor.h"
#include "MasterLevelManager.generated.h"

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

private:
	UFUNCTION()
	void UnloadCurrentLevel();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();
	UFUNCTION(BlueprintCallable)
	int GetTanksCountForNextLevel();
	UFUNCTION(BlueprintCallable)
	bool IsLastLevel();

public:
	UPROPERTY(EditAnywhere, Category = "Levels")
	TArray<TSoftObjectPtr<UWorld>> OrderedLevelsList;

	UPROPERTY(BlueprintAssignable)
	FVictoryDelegate OnVictoryDelegate;

private:
	int CurrentLevelIndex = -1;

};
