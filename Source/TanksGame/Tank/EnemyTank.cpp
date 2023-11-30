#include "EnemyTank.h"
#include "EnemyTankController.h"
#include "BrainComponent.h"
#include "PlayerTank.h"
#include "TankPlayerController.h"
#include "GameFramework/PlayerState.h"
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
	TogglePause(true);
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
	HandleFire();
}

void AEnemyTank::HandleFire_Implementation() 
{
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return;
	if (fireTimer > 0 || ProjectileCount >= TanksData->TanksData[TankType].MaxProjectileCount) return;
	fireTimer = (float)1 / TanksData->TanksData[TankType].FireRate;
	UWorld* world = GetWorld();
	if (world == nullptr) return;
	if (ProjectileSpawnPoint == nullptr) return;

	AProjectile* bullet = Cast<AProjectile>(world->SpawnActor(TanksData->TanksData[TankType].Projectile));
	bullet->SpawningActor = this;
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
	HandlePlaceMine();
}

void AEnemyTank::HandlePlaceMine_Implementation() 
{
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return;
	if (minePlaceTimer > 0 || MineCount >= TanksData->TanksData[TankType].MaxMineCount) return;
	minePlaceTimer = TanksData->TanksData[TankType].MinePlaceDelay;
	UWorld* world = GetWorld();

	if (world == nullptr) return;
	if (MineSpawnPoint == nullptr) return;
	if (MineData == nullptr) return;
	if (MineData->Mines.Contains(MineType) == false) return;
	if (MineData->Mines[MineType].Mine == nullptr) return;

	AMine* mine = Cast<AMine>(world->SpawnActor(MineData->Mines[MineType].Mine));
	mine->SpawningActor = this;
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

int AEnemyTank::GetRemainingProjectileCount()
{
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return 0;

	return (TanksData->TanksData[TankType].MaxProjectileCount - ProjectileCount);
}

void AEnemyTank::TogglePause(bool Pause) 
{
	Super::TogglePause(Pause);
	AEnemyTankController* controller = Cast<AEnemyTankController>(GetController());
	if (controller != nullptr) {
		if (Pause) {
			controller->BrainComponent->PauseLogic(FString(TEXT("Game paused")));
		}
		else {
			controller->BrainComponent->ResumeLogic(FString(TEXT("Game resumed")));
		}
	}
}

void AEnemyTank::TakeHit(AActor* SourceActor) 
{
	if (SourceActor == nullptr) return;
	APlayerTank* Player = Cast<APlayerTank>(SourceActor);
	if (Player == nullptr) return;
	ATankPlayerController* tankController = Cast<ATankPlayerController>(Player->Controller);
	if (Controller == nullptr) return;
	Controller->PlayerState->SetScore(Controller->PlayerState->GetScore() + 1);
}

void AEnemyTank::SetPlayersArray(TArray<APlayerTank*> Players)
{
	for (auto it : Players) 
	{
		PlayerTanks.Add(it);
	}
}

void AEnemyTank::AddPlayerToArray(APlayerTank* Player) 
{
	PlayerTanks.Add(Player);
}

void AEnemyTank::RemovePlayerFromArrayAtIndex(int Index)
{
	PlayerTanks.RemoveAt(Index);
}

void AEnemyTank::RemovePlayerFromArray(APlayerTank* Player) 
{
	PlayerTanks.Remove(Player);
}

void AEnemyTank::ClearPlayersArray() 
{
	PlayerTanks.Empty();
}

APlayerTank* AEnemyTank::GetPlayerFromArray(int Index)
{
	if (Index < 0 || Index >= PlayerTanks.Num()) return nullptr;
	return PlayerTanks[Index].Get();
}

APlayerTank* AEnemyTank::GetRandomPlayerFromArray() 
{
	int Index = std::rand() % PlayerTanks.Num();
	return PlayerTanks[Index].Get();
}

APlayerTank* AEnemyTank::GetClosestPlayerFromArray() 
{
	float MinDistance = MAX_flt;
	int index = -1;;
	for (int i = PlayerTanks.Num() - 1; i >= 0; i--) 
	{
		if (PlayerTanks[i].IsValid() == false)
		{
			PlayerTanks.RemoveAt(i);
			continue;
		}
		float distance = FVector::Dist(GetActorLocation(), PlayerTanks[i]->GetTargetLocation());
		if (distance < MinDistance) {
			MinDistance = distance;
			index = i;
		}
	}
	if (index < 0) return nullptr;
	return PlayerTanks[index].Get();
}

int AEnemyTank::GetPlayersArrayLength() 
{
	return PlayerTanks.Num();
}

void AEnemyTank::UpdatePlayersArray() 
{
	for (int i = PlayerTanks.Num() - 1; i >= 0; i--) 
	{
		if (PlayerTanks[i].IsValid() == false) 
		{
			PlayerTanks.RemoveAt(i);
		}
	}
}

 