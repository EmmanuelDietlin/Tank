// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "MinesData.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Tank.generated.h"

UCLASS()
class TANKSGAME_API ATank : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void TakeHit();

public:
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* PlaceMineAction;

	UPROPERTY(EditAnywhere, Category = "Mine")
	UMinesData* MineData;

	UPROPERTY(EditAnywhere, Category = "Mine")
	TEnumAsByte<MineTypes> MineType = MineTypes::StandardMine;


protected:
	class UStaticMeshComponent* Turret = nullptr;
	class UStaticMeshComponent* ProjectileSpawnPoint = nullptr;
	class UStaticMeshComponent* MineSpawnPoint = nullptr;
	float fireTimer = 0;
	float minePlaceTimer = 0;

};
