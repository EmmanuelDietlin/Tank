// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine.h"
#include "Tank.h"
#include "DestructibleWall.h"
#include "Components/SphereComponent.h"

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ExplosionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Explosion"));

}

// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mineTimer += DeltaTime;
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
	ExplosionSphere->SetSphereRadius(ExplosionRadius);
	TArray<AActor*> overlappingActors;
	ExplosionSphere->GetOverlappingActors(overlappingActors);
	for (const auto& it : overlappingActors) {
		if (ATank* tank = Cast<ATank>(it)) {
			tank->TakeHit();
		}
		else if (ADestructibleWall* wall = Cast<ADestructibleWall>(it)) {
			wall->TakeHit();
		}
	}
	Destroy();
}

