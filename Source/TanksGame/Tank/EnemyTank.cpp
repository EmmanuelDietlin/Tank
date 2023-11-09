#include "EnemyTank.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

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

void AEnemyTank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (Body == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref for tank body "));
		return;
	}
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return;

	if (NextPosition.Equals(FVector::ZeroVector)) return;

	//Forward movement
	if (fireTimer < ((float)1 / TanksData->TanksData[TankType].FireRate - MovementStopAfterFire)) {
		FVector forward = Body->GetForwardVector();
		AddMovementInput(forward, TanksData->TanksData[TankType].TankForwardSpeed);
	}

	//Rotation movement
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(Body->GetComponentLocation(), NextPosition);
	FRotator nextRotation = UKismetMathLibrary::RInterpTo(
		Body->GetComponentRotation(),
		targetRotation,
		DeltaTime,
		TanksData->TanksData[TankType].TankRotationSpeed
	);
	nextRotation.Roll = 0;
	nextRotation.Pitch = 0;
	Body->SetWorldRotation(nextRotation);

}

void AEnemyTank::Fire()
{
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return;
	if(fireTimer > 0 || ProjectileCount > TanksData->TanksData[TankType].MaxProjectileCount) return;
	fireTimer = (float)1 / TanksData->TanksData[TankType].FireRate;
	UWorld* world = GetWorld();
	if (world == nullptr) return;
	if (ProjectileSpawnPoint == nullptr) return;

	AProjectile* bullet = Cast<AProjectile>(world->SpawnActor(TanksData->TanksData[TankType].Projectile));
	bullet->SetActorLocationAndRotation(
		ProjectileSpawnPoint->GetComponentLocation(),
		Turret->GetComponentQuat());
	bullet->Speed = TanksData->TanksData[TankType].ProjectileSpeed;
	bullet->TargetTags = TanksData->TanksData[TankType].EnemyTags;
	bullet->OnDestroyed.AddDynamic(this, &AEnemyTank::ProjectileDestroyed);
	ProjectileCount++;

	if (FireSound != nullptr && TankGameInstance != nullptr) {
		UGameplayStatics::PlaySound2D(this, FireSound, FireSoundVolume * TankGameInstance->SoundVolume);
	}
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

	AMine* mine = Cast<AMine>(world->SpawnActor(MineData->Mines[MineType].Mine));
	mine->SetActorLocation(MineSpawnPoint->GetComponentLocation());
	mine->MineExplosionDelay = MineData->Mines[MineType].MineExplosionDelay;
	mine->EnemyTags = TanksData->TanksData[TankType].EnemyTags;
	mine->ExplosionRadius = MineData->Mines[MineType].MineExplosionRadius;
	mine->OnDestroyed.AddDynamic(this, &AEnemyTank::MineDestroyed);
	MineCount++;

	if (MinePlaceSound != nullptr && TankGameInstance != nullptr) {
		UGameplayStatics::PlaySound2D(this, MinePlaceSound, MinePlaceSoundVolume * TankGameInstance->SoundVolume);
	}
}

FRotator AEnemyTank::GetTurretRotation() {
	if (Turret == nullptr) return FRotator::ZeroRotator;
	return Turret->GetComponentRotation();
}

void AEnemyTank::RotateTurret(FRotator TargetRotation, double DeltaTime) {
	if (Turret == nullptr) return;
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return;
	FRotator turretRotation = UKismetMathLibrary::RInterpTo_Constant(
		Turret->GetComponentRotation(), 
		TargetRotation, 
		DeltaTime, 
		TanksData->TanksData[TankType].TurretRotationSpeed);
	turretRotation.SetComponentForAxis(EAxis::X, 0);
	turretRotation.SetComponentForAxis(EAxis::Y, 0);
	Turret->SetWorldRotation(turretRotation);
}

void AEnemyTank::SetTurretRotation(FRotator TargetRotation) {
	if (Turret == nullptr) return;
	TargetRotation.Roll = 0;
	TargetRotation.Pitch = 0;
	Turret->SetRelativeRotation(TargetRotation);
}


 