// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "TankGameInstance.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "MinesData.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDestroyedDelegate);

UCLASS(Abstract)
class TANKSGAME_API ATank : public ACharacter
{
	GENERATED_BODY()

#pragma region Methods
public:
	// Sets default values for this character's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void ProjectileDestroyed(AActor* DestroyedActor);
	UFUNCTION()
	void MineDestroyed(AActor* DestroyedActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void TakeHit();
	UFUNCTION(BlueprintCallable)
	virtual int GetRemainingProjectileCount() { unimplemented(); return 0; };
	UFUNCTION(BlueprintCallable)
	virtual void TogglePause(bool Pause);
#pragma endregion

#pragma region Fields
public:
	UPROPERTY(EditAnywhere, Category = "Mine")
	UMinesData* MineData;

	UPROPERTY(EditAnywhere, Category = "Mine")
	TEnumAsByte<MineTypes> MineType = MineTypes::EnemyStandadMine;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float MovementStopAfterFire = .05f;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundWave* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	float ExplosionSoundVolume = .2f UMETA(ClampMin = 0f, ClampMax = 1f);
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundWave* FireSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	float FireSoundVolume = .5f UMETA(ClampMin = 0f, ClampMax = 1f);

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundWave* MinePlaceSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	float MinePlaceSoundVolume= .5f UMETA(ClampMin = 0f, ClampMax = 1f);

	UPROPERTY(BlueprintAssignable)
	FTankDestroyedDelegate OnTankDestroyed;


protected:
	class UStaticMeshComponent* Turret = nullptr;
	class UStaticMeshComponent* Body = nullptr;
	class UStaticMeshComponent* ProjectileSpawnPoint = nullptr;
	class UStaticMeshComponent* MineSpawnPoint = nullptr;
	class UTankGameInstance* TankGameInstance = nullptr;
	float fireTimer = 0;
	float minePlaceTimer = 0;
	int ProjectileCount = 0;
	int MineCount = 0;
	bool IsPaused = false;
#pragma endregion
};
