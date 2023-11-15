// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "EnemyTank.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "MasterLevelManager.h"

// Sets default values
AMasterLevelManager::AMasterLevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasterLevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AMasterLevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterLevelManager::LoadNextLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Load next level"));
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), OrderedLevelsList[CurrentLevelIndex + 1], true, false, LatentInfo);
	CurrentLevelIndex++;
}

void AMasterLevelManager::RestartLevel() 
{
	UE_LOG(LogTemp, Warning, TEXT("Unload current level"));
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName(TEXT("LoadCurrentLevel"));
	LatentInfo.UUID = 2;
	LatentInfo.Linkage = 0;
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), OrderedLevelsList[CurrentLevelIndex], LatentInfo, false);
}

void AMasterLevelManager::LoadCurrentLevel() 
{
	UE_LOG(LogTemp, Warning, TEXT("Reload current level"));
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), OrderedLevelsList[CurrentLevelIndex], true, false, LatentInfo);
}

void AMasterLevelManager::UnloadCurrentLevel() 
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), OrderedLevelsList[CurrentLevelIndex], LatentInfo, true);
}

void AMasterLevelManager::NextLevel() 
{
	UE_LOG(LogTemp, Warning, TEXT("erfererrerrererrererereer"));
	if (OrderedLevelsList.Num() <= 0) return;
	if (TimerHandle.IsValid()) 
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);;
	}
	if (CurrentLevelIndex + 1 > OrderedLevelsList.Num()) {
		OnVictoryDelegate.Broadcast();
	}
	else
	{
		FLatentActionInfo LatentInfo;
		if (CurrentLevelIndex >= 0) {
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = FName(TEXT("LoadNextLevel"));
			LatentInfo.UUID = 1;
			LatentInfo.Linkage = 0;
			UE_LOG(LogTemp, Warning, TEXT("Unload previous level"));
			UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), OrderedLevelsList[CurrentLevelIndex], LatentInfo, false);
		}
		else {
			LoadNextLevel();
		}
		//if (CurrentLevelIndex > 0) {
		//	FName MapName = OrderedLevelsList[CurrentLevelIndex - 1]->GetFName();
		//	bool a = UGameplayStatics::GetStreamingLevel(this, MapName)->IsLevelLoaded();
		//	UE_LOG(LogTemp, Warning, TEXT("fjnrejkeng : %i"), a);
		//	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, OrderedLevelsList[CurrentLevelIndex - 1], LatentInfo, false);
		//	//UGameplayStatics::UnloadStreamLevel(this, MapName, LatentInfo, false);
		//}
	}
}

void AMasterLevelManager::NextLevelWithDelay(float Delay)
{
	if (OrderedLevelsList.Num() <= 0) return;
	if (CurrentLevelIndex + 1 > OrderedLevelsList.Num()) {
		OnVictoryDelegate.Broadcast();
	}
	else
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMasterLevelManager::NextLevel, Delay, false);
	}
}

void AMasterLevelManager::LoadMainMenu() 
{
	OnMainMenu.Broadcast();
}

int AMasterLevelManager::GetTanksCountForNextLevel() {
	//TODO => remplacer par le vrai compte !
	//Deux solutions : 
	// - 1 : Data avec lien entre nom niveau et nombre de tanks => facilité mais mise à jour peut être oubliée
	//- 2 : Compter le nombre de tanks juste avant de loader le niveau => coût temporel possiblement important
	return 1;
}

bool AMasterLevelManager::IsLastLevel() 
{
	return CurrentLevelIndex == OrderedLevelsList.Num();

}


