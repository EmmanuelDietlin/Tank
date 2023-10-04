// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Tank.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	auto shapeComponent = FindComponentByClass<UCapsuleComponent>(); //Type de composant de collision
	if (shapeComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
		return;
	}
	shapeComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OverlapBegin);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector position = GetActorLocation();
	FVector forward = GetActorForwardVector();
	SetActorLocation(position + forward * Speed * DeltaTime);
}

void AProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (ATank* tank = Cast<ATank>(OtherActor)) {
		for (const auto& tag : TargetTags) {
			if (tank->Tags.Contains(tag) == true) {
				tank->TakeHit(Damage);
				Destroy();
				return;
			}
		}
	}
}

