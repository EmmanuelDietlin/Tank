// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Debug) return;
	int remainingTanks = 0;
	for (int i = EnemyTanks.Num() - 1; i >= 0; i--) {
		if (EnemyTanks[i].IsValid()) {
			remainingTanks++;
		}
	}
	if (remainingTanks == 0) {
		if (LevelEnded == false) {
			if (IsLastLevel == false) {
				OnNextLevelDelegate.Broadcast();
			}
			else {
				OnVictoryDelegate.Broadcast();
			}
			LevelEnded = true;
		}
		if (IsLastLevel == false) {
			if (LevelChangeTimer >= NextLevelTimer) {
				UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextLevel);
			}
			LevelChangeTimer += DeltaTime;
		}
	}
	RemainingTanks = remainingTanks;
}

