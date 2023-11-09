// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
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

#pragma region Methods
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int GetRemainingProjectileCount() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Function to move the tank forward
	void Move(const FInputActionValue& value);

	//Function to fire a projectile
	void Fire(const FInputActionValue& value);

	//Function to place a mine 
	void PlaceMine(const FInputActionValue& value);

	//Function triggered on hit
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion

#pragma region Fields
private:
	APlayerController* PlayerController;
	FVector MousePosition;
	UCapsuleComponent* Collision = nullptr;
	UCharacterMovementComponent* CharacterMovement = nullptr;

	float ZRotationSpeed = 0;

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

	UPROPERTY(EditAnywhere, Category = "Projectile")
	int MaxProjectileCount = 1;

	UPROPERTY(EditAnywhere, Category = "Mine")
	int MaxMineCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inputs")
	float TurretRotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TArray<FString> EnemyTags = { "Enemy" };

	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputAction* PlaceMineAction;

#pragma endregion
};
