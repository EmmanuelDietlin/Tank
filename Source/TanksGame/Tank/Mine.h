// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Mine.generated.h"

UCLASS()
class TANKSGAME_API AMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadonly)
	TArray<FString> EnemyTags = { "Enemy" };

	float MineExplosionDelay = 2;
	float ExplosionRadius = 1;

private:
	float mineTimer = 0;
	USphereComponent* ExplosionSphere;

};
