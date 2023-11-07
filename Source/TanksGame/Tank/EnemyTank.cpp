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

void AEnemyTank::EndPlay(const EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);
	if (TankGameInstance == nullptr) return;
	TankGameInstance->Score += 1;
}

void AEnemyTank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (Body == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref for tank body "));
		return;
	}
	if (TanksData == nullptr || TanksData->TanksData.Contains(TankType) == false) return;
	
	/*FQuat currentRotation = Body->GetComponentQuat();
	FRotator nextRotation = FRotator::ZeroRotator;
	nextRotation.SetComponentForAxis(EAxis::Z, ZRotationSpeed * DeltaTime);
	currentRotation *= nextRotation.Quaternion();
	Body->SetWorldRotation(currentRotation);*/

	/*FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NextPosition);
	targetRotation.Yaw = FMath::Min(targetRotation.Yaw, TanksData->TanksData[TankType].TankRotationSpeed * DeltaTime * .001);
	targetRotation.SetComponentForAxis(EAxis::X, 0);
	targetRotation.SetComponentForAxis(EAxis::Y, 0);
	FQuat currentRotation = Body->GetComponentQuat();
	currentRotation *= targetRotation.Quaternion();
	Body->SetWorldRotation(currentRotation);*/


	if (NextPosition.Equals(FVector::ZeroVector)) return;
	/*
	FQuat currentRotation = Body->GetComponentQuat();
	FRotator nextRotation = FRotator::ZeroRotator;
	float sign = targetRotation.Yaw / FMath::Abs(targetRotation.Yaw);
	nextRotation.SetComponentForAxis(
		EAxis::Z, 
		sign * FMath::Min(TanksData->TanksData[TankType].TankRotationSpeed * DeltaTime, FMath::Abs(targetRotation.Yaw)));
	currentRotation *= nextRotation.Quaternion();*/
	/*Body->SetWorldRotation(nextRotation);
	UE_LOG(LogTemp, Warning, TEXT("Rotation = %s"), *nextRotation.ToString());*/
	//targetRotation.SetComponentForAxis(EAxis::Z, FMath::Min(targetRotation.GetComponentForAxis(EAxis::Z), TanksData->TanksData[TankType].TankRotationSpeed * DeltaTime));
	/*targetRotation.SetComponentForAxis(EAxis::X, 0);
	targetRotation.SetComponentForAxis(EAxis::Y, 0);
	Body->SetWorldRotation(targetRotation);*/
	//UE_LOG(LogTemp, Warning, TEXT("Rotation = %d"), targetRotation.GetComponentForAxis(EAxis::Z));
	/*FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NextPosition);
	FRotator deltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(Body->GetComponentRotation(), targetRotation);
	targetRotation.Roll = 0;
	targetRotation.Pitch = 0;
	UE_LOG(LogTemp, Warning, TEXT("Rotation = %s"), *targetRotation.ToString());*/
	/*if (targetRotation.Yaw < 0) {
		targetRotation.Yaw = -1 * FMath::Min(FMath::Abs(targetRotation.Yaw), TanksData->TanksData[TankType].TankRotationSpeed * DeltaTime);
		UE_LOG(LogTemp, Warning, TEXT("New Rotation invert = %s"), *targetRotation.ToString());;
	}
	else {
		targetRotation.Yaw = FMath::Min(FMath::Abs(targetRotation.Yaw), TanksData->TanksData[TankType].TankRotationSpeed * DeltaTime);
		UE_LOG(LogTemp, Warning, TEXT("New Rotation = %s"), *targetRotation.ToString());;
	}*/

	//VOIR ICI POUR LA ROTATION
	//https://forums.unrealengine.com/t/how-to-rotate-my-tank-turret-around-local-z-axis/651425/4

	/*FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NextPosition);
	Body->SetRelativeRotation(targetRotation);*/
	//Body->SetWorldRotation(targetRotation);

	////TRANSLATION OK
	//FVector2D actor2Dpos(GetActorLocation().X, GetActorLocation().Y);
	//FVector2D target2DPos(NextPosition.X, NextPosition.Y);
	//if (actor2Dpos != target2DPos) {
	FVector forward = Body->GetForwardVector();
	AddMovementInput(forward, TanksData->TanksData[TankType].TankForwardSpeed);

	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(Body->GetComponentLocation(), NextPosition);
	FRotator nextRotation = UKismetMathLibrary::RInterpTo(
		Body->GetComponentRotation(),
		targetRotation,
		DeltaTime,
		TanksData->TanksData[TankType].TankRotationSpeed
	);
	nextRotation.Roll = 0;
	nextRotation.Pitch = 0;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *targetRotation.ToString());
	Body->SetWorldRotation(nextRotation);
	//}
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

void AEnemyTank::SetTargetPosition(FVector Position) {
	if (Body == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref for tank body "));
		return;
	}
	NextPosition = Position;
}
 