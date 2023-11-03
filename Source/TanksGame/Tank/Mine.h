// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "TankGameInstance.h"
#include "GameFramework/Actor.h"
#include "Mine.generated.h"

UCLASS()
class TANKSGAME_API AMine : public AActor
{
	GENERATED_BODY()

#pragma region Methods
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void Explode();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AMine();
#pragma endregion

#pragma region Fields
public:
	UPROPERTY(BlueprintReadonly)
	TArray<FString> EnemyTags = { "Enemy" };

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundWave* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	float ExplosionSoundVolume = .2f UMETA(ClampMin = 0f, ClampMax = 1f);

	float MineExplosionDelay = 2;
	float ExplosionRadius = 1;

private:
	float mineTimer = 0;
	USphereComponent* ExplosionSphere;
	UTankGameInstance* TankGameInstance = nullptr;


#pragma endregion

};
