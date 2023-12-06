#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


void APlayerTank::BeginPlay() 
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref for player controller"));
	}

	CharacterMovement = GetCharacterMovement();
	if (CharacterMovement == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref for character movement component"));
	}

	Collision = Cast<UCapsuleComponent>(GetRootComponent());
	if (Collision == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref to collision"));
		return;
	}
	Collision->OnComponentHit.AddDynamic(this, &APlayerTank::OnHit);
}

void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerController == nullptr) return;
	if (Turret == nullptr) return;

	FHitResult hitResult;
	if (PlayerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult) == false) {
		return;
	}
	if (MousePosition != hitResult.Location) {
		MousePosition = hitResult.Location;
	}
	FVector turretWorldLoc = Turret->GetComponentLocation();
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(turretWorldLoc, MousePosition);
	/*FRotator turretRotation = UKismetMathLibrary::RInterpTo_Constant(Turret->GetComponentRotation(), targetRotation, DeltaTime, TurretRotationSpeed);
	turretRotation.SetComponentForAxis(EAxis::X, 0);
	turretRotation.SetComponentForAxis(EAxis::Y, 0);
	Turret->SetWorldRotation(turretRotation);*/


	if (Body == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref for tank body "));
		return;
	}
	FQuat currentRotation = Body->GetComponentQuat();
	FRotator nextRotation = FRotator::ZeroRotator;
	nextRotation.SetComponentForAxis(EAxis::Z, ZRotationSpeed * DeltaTime);
	currentRotation *= nextRotation.Quaternion();
	/*Body->SetWorldRotation(currentRotation);*/

	HandleRotations(targetRotation, currentRotation, DeltaTime);
	ZRotationSpeed = 0;

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
	if (IsPaused == true) return;
	if (fireTimer >= ((float)1 / FireRate - MovementStopAfterFire)) {
		return;
	}
	FVector2d vector = value.Get<FVector2d>();
	if (Body == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref for tank body "));
		return;
	}
	FVector forward = Body->GetForwardVector();
	AddMovementInput(forward, vector.Y * ForwardSpeed);
	ZRotationSpeed = vector.X * RotationSpeed;
}

void APlayerTank::HandleRotations_Implementation(FRotator TurretTargetRotation, FQuat BodyTargetRotation, double DeltaTime)
{
	FRotator turretRotation = UKismetMathLibrary::RInterpTo_Constant(Turret->GetComponentRotation(), TurretTargetRotation, DeltaTime, TurretRotationSpeed);
	turretRotation.SetComponentForAxis(EAxis::X, 0);
	turretRotation.SetComponentForAxis(EAxis::Y, 0);
	Turret->SetWorldRotation(turretRotation);

	Body->SetWorldRotation(BodyTargetRotation);
}

void APlayerTank::Fire(const FInputActionValue& value) 
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed fire"));
	HandleFire();
}

void APlayerTank::HandleFire_Implementation() 
{
	UE_LOG(LogTemp, Warning, TEXT("is paused : %i"), IsPaused);
	if (IsPaused == true) return;
	if (fireTimer > 0 || ProjectileCount >= MaxProjectileCount) return;
	fireTimer = (float)1 / FireRate;
	UWorld* world = GetWorld();
	if (world == nullptr) return;
	if (ProjectileSpawnPoint == nullptr) return;

	AProjectile* bullet = Cast<AProjectile>(world->SpawnActor(Projectile));
	bullet->SpawningActor = this->Controller;
	bullet->SetActorLocationAndRotation(
		ProjectileSpawnPoint->GetComponentLocation(),
		Turret->GetComponentQuat());
	bullet->Speed = ProjectileSpeed;
	bullet->TargetTags = EnemyTags;
	bullet->OnDestroyed.AddDynamic(this, &APlayerTank::ProjectileDestroyed);
	ProjectileCount++;

	TankGameInstance = Cast<UTankGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (FireSound != nullptr && TankGameInstance != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%f"), TankGameInstance->SoundVolume);
		UGameplayStatics::PlaySound2D(this, FireSound, FireSoundVolume * TankGameInstance->SoundVolume);
	}
}

void APlayerTank::PlaceMine(const FInputActionValue& value) 
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed place mine"));
	HandlePlaceMine();
}

void APlayerTank::HandlePlaceMine_Implementation() 
{
	UE_LOG(LogTemp, Warning, TEXT("is paused : %i"), IsPaused);
	if (IsPaused == true) return;
	if (minePlaceTimer > 0 || MineCount >= MaxMineCount) return;
	UWorld* world = GetWorld();

	if (world == nullptr) return;
	if (MineSpawnPoint == nullptr) return;
	if (MineData == nullptr) return;
	if (MineData->Mines.Contains(MineType) == false) return;
	if (MineData->Mines[MineType].Mine == nullptr) return;

	minePlaceTimer = MinePlaceDelay;
	AMine* mine = Cast<AMine>(world->SpawnActor(MineData->Mines[MineType].Mine));
	if (mine == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Could not spawn mine"));
		return;
	}
	mine->SpawningActor = this->Controller;
	mine->SetActorLocation(MineSpawnPoint->GetComponentLocation());
	mine->MineExplosionDelay = MineData->Mines[MineType].MineExplosionDelay;
	mine->EnemyTags = EnemyTags;
	mine->ExplosionRadius = MineData->Mines[MineType].MineExplosionRadius;
	mine->OnDestroyed.AddDynamic(this, &APlayerTank::MineDestroyed);
	MineCount++;

	TankGameInstance = Cast<UTankGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (MinePlaceSound != nullptr && TankGameInstance != nullptr) {
		UGameplayStatics::PlaySound2D(this, MinePlaceSound, MinePlaceSoundVolume * TankGameInstance->SoundVolume);
	}
}

void APlayerTank::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Body == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Body is null"));
		return;
	}
	FVector forward = Body->GetForwardVector();
	forward.Normalize();
	FVector normal = Hit.Normal;
	normal.Normalize();
	if (forward.Dot(normal) < -.1f) {
		CharacterMovement->Velocity = FVector::Zero();
	}
}

int APlayerTank::GetRemainingProjectileCount() {
	return MaxProjectileCount - ProjectileCount;
}

