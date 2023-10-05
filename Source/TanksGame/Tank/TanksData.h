// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Engine/DataAsset.h"
#include "TanksData.generated.h"

USTRUCT()
struct FTankData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileSpeed = 1 UMETA(ClampMin = "0");

	UPROPERTY(EditAnywhere, Category = "Projectile")
	int ProjectileDamage = 1 UMETA(ClampMin = "0");

	UPROPERTY(EditAnywhere, Category = "Tank")
	float TankRotationSpeed = 1 UMETA(ClampMin = "0");

	UPROPERTY(EditAnywhere, Category = "Tank")
	float TankForwardSpeed = 1 UMETA(ClampMin = "0");

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float FireRate = 1;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TArray<FString> EnemyTags = { "Player" };
};

UCLASS()
class TANKSGAME_API UTanksData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FTankData> TanksData;
};

UENUM()
enum TankTypes {
	BasicTank UMETA(DisplayName = "BasicTank"),
	MineTank UMETA(DisplayName = "MineTank"),
	FastTank UMETA(DisplayName = "FastTank"),
	FireTank UMETA(DisplayName = "FireTank")
};


