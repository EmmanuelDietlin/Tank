// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"



APlayerTank::APlayerTank() 
{

}

void APlayerTank::BeginPlay() 
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
}

void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (fireTimer > 0) fireTimer -= DeltaTime;
	if (minePlaceTimer > 0) minePlaceTimer -= DeltaTime;
}

void APlayerTank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	// Get the player controller
	auto playerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	//Add the input mapping context
	eiSubsystem->AddMappingContext(Context, 0);

	// Get the EnhancedInputComponent
	auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind Move() to the mapping
	//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
	//ETriggerEvent is an enum, where Triggered means "button is held down".
	playerEIcomponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerTank::Move);
	playerEIcomponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerTank::Fire);
	playerEIcomponent->BindAction(PlaceMineAction, ETriggerEvent::Triggered, this, &APlayerTank::PlaceMine);
}

void APlayerTank::Move(const FInputActionValue& value) {
	FVector2d vector = value.Get<FVector2d>();
	FVector forward = GetActorForwardVector();
	AddMovementInput(forward, vector.Y * ForwardSpeed);
	AddControllerYawInput(vector.X * RotationSpeed * 2 * PI / 360);
}

void APlayerTank::Fire(const FInputActionValue& value) 
{
	if (fireTimer > 0) return;
	fireTimer = (float)1 / FireRate;
	UWorld* world = GetWorld();
	if (world == nullptr) return;
	if (ProjectileSpawnPoint == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("Fire Projectile"));
	AProjectile* bullet = Cast<AProjectile>(world->SpawnActor(Projectile));
	bullet->SetActorLocationAndRotation(
		ProjectileSpawnPoint->GetComponentLocation(),
		Turret->GetComponentQuat());
	bullet->Speed = ProjectileSpeed;
	bullet->TargetTags = EnemyTags;
}

void APlayerTank::PlaceMine(const FInputActionValue& value) 
{
	if (minePlaceTimer > 0) return;
	minePlaceTimer = MinePlaceDelay;
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
	mine->EnemyTags = EnemyTags;
	mine->ExplosionRadius = MineData->Mines[MineType].MineExplosionRadius;
}
