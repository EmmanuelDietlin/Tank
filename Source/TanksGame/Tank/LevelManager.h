// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTank.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

UCLASS()
class TANKSGAME_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

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
	UWorld* NextLevel;

};
