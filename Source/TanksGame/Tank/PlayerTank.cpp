// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"



APlayerTank::APlayerTank() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerTank::BeginPlay() 
{
	Super::BeginPlay();
	Turret = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("TurretElement")));
	if (Turret == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null ref to turret"));
	}
}

void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void APlayerTank::Fire(const FInputActionValue& value) {

}

void APlayerTank::PlaceMine(const FInputActionValue& value) {

}
