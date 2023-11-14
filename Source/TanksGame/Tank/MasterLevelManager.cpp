// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "EnemyTank.h"
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
	if (OrderedLevelsList.Num() <= 0) return;
	if (CurrentLevelIndex + 1 > OrderedLevelsList.Num()) {
		OnVictoryDelegate.Broadcast();
	}
	else 
	{
		//Impl�menter un timer pour d�marrer le chargement apr�s un certain d�lai
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("UnloadCurrentLevel");
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, OrderedLevelsList[CurrentLevelIndex + 1], true, false, LatentInfo);
	}
}



void AMasterLevelManager::UnloadCurrentLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("aaaa"));
	if (OrderedLevelsList.Num() <= 0) return;
	FLatentActionInfo LatentInfo;
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, OrderedLevelsList[CurrentLevelIndex], LatentInfo, false);
	CurrentLevelIndex++;
}

int AMasterLevelManager::GetTanksCountForNextLevel() {
	//TODO => remplacer par le vrai compte !
	//Deux solutions : 
	// - 1 : Data avec lien entre nom niveau et nombre de tanks => facilit� mais mise � jour peut �tre oubli�e
	//- 2 : Compter le nombre de tanks juste avant de loader le niveau => co�t temporel possiblement important
	return 1;
}

bool AMasterLevelManager::IsLastLevel() 
{
	return CurrentLevelIndex == OrderedLevelsList.Num();

}

