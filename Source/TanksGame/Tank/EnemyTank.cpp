// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"

void AEnemyTank::BeginPlay() {
	Super::BeginPlay();
	UGameInstance* instance = GetGameInstance();
	if (instance == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No game instance could be found"));
		return;
	}
	TankGameInstance = Cast<UTankGameInstance>(instance);
	if (TankGameInstance == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Game instance is not of type UTankGameInstance"));
	}
}

void AEnemyTank::EndPlay(const EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);
	if (TankGameInstance == nullptr) return;
	TankGameInstance->Score += 1;
}

void AEnemyTank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AEnemyTank::Fire()
{
	if (fireTimer > 0) return;
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return;
	fireTimer = (float)1 / TanksData->TanksData[TankType].FireRate;
	UWorld* world = GetWorld();
	if (world == nullptr) return;
	if (ProjectileSpawnPoint == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("Fire Projectile"));
	AProjectile* bullet = Cast<AProjectile>(world->SpawnActor(TanksData->TanksData[TankType].Projectile));
	bullet->SetActorLocationAndRotation(
		ProjectileSpawnPoint->GetComponentLocation(),
		Turret->GetComponentQuat());
	bullet->Speed = TanksData->TanksData[TankType].ProjectileSpeed;
	bullet->TargetTags = TanksData->TanksData[TankType].EnemyTags;
}

void AEnemyTank::PlaceMine()
{
	if (minePlaceTimer > 0) return;
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return;
	minePlaceTimer = TanksData->TanksData[TankType].MinePlaceDelay;
	UWorld* world = GetWorld();

	if (world == nullptr) return;
	if (MineSpawnPoint == nullptr) return;
	if (MineData == nullptr) return;
	if (MineData->Mines.Contains(MineType) == false) return;
	if (MineData->Mines[MineType].Mine == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("Place Mine"));
	AMine* mine = Cast<AMine>(world->SpawnActor(MineData->Mines[MineType].Mine));
	mine->SetActorLocation(MineSpawnPoint->GetComponentLocation());
	mine->MineExplosionDelay = MineData->Mines[MineType].MineExplosionDelay;
	mine->EnemyTags = TanksData->TanksData[TankType].EnemyTags;
	mine->ExplosionRadius = MineData->Mines[MineType].MineExplosionRadius;
}
 