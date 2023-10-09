// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TanksData.h"
#include "CoreMinimal.h"
#include "TankGameInstance.h"
#include "Tank.h"
#include "EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class TANKSGAME_API AEnemyTank : public ATank
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Tank")
	class UTanksData* TanksData;

	UPROPERTY(EditAnywhere, Category = "Tank")
	TEnumAsByte<TankTypes> TankType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

public:
	void Fire();
	void PlaceMine();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UTankGameInstance* TankGameInstance;

};

