// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundWave.h"
#include "TankGameInstance.h"
#include "TankGameMode.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKSGAME_API AProjectile : public AActor
{
	GENERATED_BODY()

#pragma region Methods
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void ToggleTick(bool Pause);
	UFUNCTION()
	void BeginDestroy() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AProjectile();
#pragma endregion

#pragma region Fields
public:
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Sounds")
	USoundWave* BounceSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Sounds")
	float BounceSoundVolume = .5f UMETA(ClampMin = 0f, ClampMax = 1f);

	UPROPERTY(BlueprintReadonly)
	float Speed = 10;
	int Damage = 1;
	UPROPERTY(BlueprintReadWrite)
	int Bounces = 1;
	UPROPERTY(BlueprintReadonly)
	TArray<FString> TargetTags = { "Enemy" };
	UPROPERTY(BlueprintReadonly)
	AActor* SpawningActor;

protected:
	UPROPERTY(BlueprintReadonly)
	UTankGameInstance* TankGameInstance = nullptr;
	ATankGameMode* TankGameMode;
#pragma endregion
};
