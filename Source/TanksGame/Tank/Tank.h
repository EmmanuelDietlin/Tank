// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankGameInstance.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "MinesData.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDestroyedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTankDestroyedByActorDelegate, AActor*, SourceActor, AActor*, DestroyedActor);

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
	UFUNCTION(Server, Reliable)
	virtual void HandleTakeHit(AActor* SourceActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UFUNCTION(BlueprintNativeEvent)
	void PhysicsTick(float SubstepDeltaTime);
	virtual void PhysicsTick_Implementation(float SubstepDeltaTime);
	FCalculateCustomPhysics OnCalculateCustomPhysics;
	void CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance);*/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void TakeHit(AActor* SourceActor);

	UFUNCTION(BlueprintCallable)
	virtual int GetRemainingProjectileCount() { unimplemented(); return 0; };
	UFUNCTION(BlueprintCallable)
	virtual void TogglePause(bool Pause);
	UFUNCTION(BlueprintCallable)
	void SetTurretRotation(FRotator TargetRotation);
	UFUNCTION(BlueprintCallable)
	void SetBodyRotation(FRotator TargetRotation);

	/*UFUNCTION(Server, Reliable)
	virtual void HandleFire();
	UFUNCTION(Server, Reliable)
	virtual void HandlePlaceMine();*/
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

	UPROPERTY(BlueprintAssignable)
	FTankDestroyedByActorDelegate OnTankDestroyedByActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsPaused = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanBeDestroyed = true;

protected:
	class UStaticMeshComponent* Turret = nullptr;
	class UStaticMeshComponent* Body = nullptr;
	class UStaticMeshComponent* ProjectileSpawnPoint = nullptr;
	class UStaticMeshComponent* MineSpawnPoint = nullptr;
	class UTankGameInstance* TankGameInstance = nullptr;
	class UCapsuleComponent* Root = nullptr;
	float fireTimer = 0;
	float minePlaceTimer = 0;
	int ProjectileCount = 0;
	int MineCount = 0;
	float PauseAfterShoot = 0;
#pragma endregion
};
