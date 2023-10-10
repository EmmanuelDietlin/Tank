// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerTank.generated.h"

/**
 * 
 */
UCLASS()
class TANKSGAME_API APlayerTank : public ATank
{
	GENERATED_BODY()

public:
	APlayerTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Move(const FInputActionValue& value);
	void Fire(const FInputActionValue& value);
	void PlaceMine(const FInputActionValue& value);

	APlayerController* PlayerController;
	FVector MousePosition;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputMappingContext* Context;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float FireRate = 1;

	UPROPERTY(EditAnywhere, Category = "Mine")
	float MinePlaceDelay = 1;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileSpeed = 1 UMETA(ClampMin = "0");

	UPROPERTY(EditAnywhere, Category = "Inputs")
	float ForwardSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inputs")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inputs")
	float TurretRotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TArray<FString> EnemyTags = { "Enemy" };
	
};
