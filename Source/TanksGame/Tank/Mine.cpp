// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine.h"
#include "Tank.h"
#include "LevelManager.h"
#include "DestructibleWall.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankGameInstance.h"

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();
	TankGameInstance = Cast<UTankGameInstance>(UGameplayStatics::GetGameInstance(this));
	ExplosionSphere = Cast<USphereComponent>(RootComponent);
	if (ExplosionSphere == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("NULL ref for explosion sphere"));
		return;
	}
	ExplosionSphere->SetSphereRadius(DefaultExplosionRadius);

	ALevelManager* LevelManager = Cast<ALevelManager>(UGameplayStatics::GetActorOfClass(this, ALevelManager::StaticClass()));
	if (LevelManager != nullptr)
	{
		LevelManager->OnPauseDelegate.AddDynamic(this, &AMine::ToggleTick);
	}
}

void AMine::ToggleTick(bool Pause) 
{
	SetActorTickEnabled(!Pause);
}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CanExplode == false) return;

	mineTimer += DeltaTime;
	if (ExplosionSphere != nullptr && ExplosionSphere->GetUnscaledSphereRadius() != ExplosionRadius) {
		ExplosionSphere->SetSphereRadius(ExplosionRadius);
	}

	if (mineTimer > MineExplosionDelay) {
		Explode();
	}
}

void AMine::Explode() 
{
	if (ExplosionSphere == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("NULL ref for explosion sphere"));
		return;
	}
	TArray<AActor*> overlappingActors;
	ExplosionSphere->GetOverlappingActors(overlappingActors);
	if (GetLocalRole() == ROLE_Authority) {
		for (const auto& it : overlappingActors) {
			if (ATank* tank = Cast<ATank>(it)) {
				tank->TakeHit();
			}
			else if (ADestructibleWall* wall = Cast<ADestructibleWall>(it)) {
				wall->TakeHit();
			}
		}
	}
	if (ExplosionSound != nullptr && TankGameInstance != nullptr) {
		UGameplayStatics::PlaySound2D(this, ExplosionSound, ExplosionSoundVolume * TankGameInstance->SoundVolume);
	}
	Destroy();
}



