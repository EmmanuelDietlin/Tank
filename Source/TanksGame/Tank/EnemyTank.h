// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TanksData.h"
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

};

