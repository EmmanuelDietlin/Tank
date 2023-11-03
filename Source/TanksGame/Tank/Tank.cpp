// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "TankGameInstance.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ATank::ATank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	Turret = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("TurretElement")));
	if (Turret == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref to turret"));
	}

	ProjectileSpawnPoint = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("ProjectileSpawnPoint")));
	if (ProjectileSpawnPoint == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref to projectile spawn point"));
	}

	MineSpawnPoint = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("MineSpawnPoint")));
	if (MineSpawnPoint == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref to mine spawn point"));
	}

	Body = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("BodyElement")));
	if (Body == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref to body component"))
	}

	TankGameInstance = Cast<UTankGameInstance>(UGameplayStatics::GetGameInstance(this));
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (fireTimer > 0) fireTimer -= DeltaTime;
	if (minePlaceTimer > 0) minePlaceTimer -= DeltaTime;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::TakeHit()
{
	if (ExplosionSound != nullptr && TankGameInstance != nullptr) {
		UGameplayStatics::PlaySound2D(this, ExplosionSound, ExplosionSoundVolume * TankGameInstance->SoundVolume);
	}
	OnTankDestroyed.Broadcast();
	bool e = Destroy();
}

void ATank::ProjectileDestroyed(AActor* DestroyedActor) {
	ProjectileCount--;
}

void ATank::MineDestroyed(AActor* DestroyedActor) {
	MineCount--;
}
