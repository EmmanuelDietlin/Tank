// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelManager.h"
#include "EnemyTankController.h"
#include "BrainComponent.h"
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
	CurrentLevel = UGameplayStatics::GetCurrentLevelName(this);
	MasterLevelManager = Cast<AMasterLevelManager>(UGameplayStatics::GetActorOfClass(this, AMasterLevelManager::StaticClass()));
	Player = Cast<APlayerTank>(UGameplayStatics::GetActorOfClass(this, APlayerTank::StaticClass()));
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SwitchLevelOnComplete == false) return;
	int remainingTanks = 0;
	for (int i = EnemyTanks.Num() - 1; i >= 0; i--) {
		if (EnemyTanks[i].IsValid()) {
			remainingTanks++;
		}
	}
	if (remainingTanks == 0) {
		if (LevelEnded == false) {
			OnNextLevelDelegate.Broadcast();
			LevelEnded = true;
		}
	}
	RemainingTanks = remainingTanks;
}

void ALevelManager::TogglePause(bool Pause) 
{
	OnPauseDelegate.Broadcast(Pause);
	UE_LOG(LogTemp, Warning, TEXT("Pause"));
	for (auto it : EnemyTanks) {
		if (it.IsValid()) {
			it->TogglePause(Pause);
			AEnemyTankController* controller = Cast<AEnemyTankController>(it->GetController());
			if (controller != nullptr) {
				if (Pause) {
					controller->BrainComponent->PauseLogic(FString(TEXT("Game paused")));
				}
				else {
					controller->BrainComponent->ResumeLogic(FString(TEXT("Game resumed")));
				}	
			}
		}
	}
	if (Player == nullptr) {
		Player = Cast<APlayerTank>(UGameplayStatics::GetActorOfClass(this, APlayerTank::StaticClass()));
	}
	if (Player != nullptr) {
		Player->TogglePause(Pause);
	}
}

void ALevelManager::LoadMainMenu() 
{
	if (LevelStreamingEnabled == true)
	{
		if (MasterLevelManager == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No master level manager found, one is needed when level streaming is enabled"));
			return;
		}
		MasterLevelManager->LoadMainMenu();
	}
	else
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenu);
	}
}

void ALevelManager::RestartLevel() 
{
	if (LevelStreamingEnabled == true) 
	{
		if (MasterLevelManager == nullptr) 
		{
			UE_LOG(LogTemp, Warning, TEXT("No master level manager found, one is needed when level streaming is enabled"));
			return;
		}
		MasterLevelManager->RestartLevel();
	}
	else 
	{
		UGameplayStatics::OpenLevel(this, FName(*CurrentLevel));
	}
}

void ALevelManager::LoadNextLevel() 
{
	if (LevelStreamingEnabled == true)
	{
		if (MasterLevelManager == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No master level manager found, one is needed when level streaming is enabled"));
			return;
		}
		MasterLevelManager->NextLevel();
	}
	else
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextLevel);
	}
}

//These two following methods set the number of tanks for each level in the corresponding data asset
void ALevelManager::PostLoad() {
#if WITH_EDITOR
	Super::PostLoad();
	CurrentLevel = UGameplayStatics::GetCurrentLevelName(this);
	if (LevelsData == nullptr) return;
	LevelsData->SetDataForLevel(UGameplayStatics::GetCurrentLevelName(this), EnemyTanks.Num());
#endif
}

void ALevelManager::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) 
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (LevelsData == nullptr) return;
	LevelsData->SetDataForLevel(*CurrentLevel, EnemyTanks.Num());
}


