// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Tank.h"
#include "Components/SphereComponent.h"

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
	auto shapeComponent = FindComponentByClass<USphereComponent>(); 
	if (shapeComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
		return;
	}
	shapeComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OverlapBegin);
	shapeComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector position = GetActorLocation();
	FVector forward = GetActorForwardVector();
	auto shapeComponent = FindComponentByClass<USphereComponent>();
	FHitResult* hit = nullptr;
	SetActorLocation(position + forward * Speed * DeltaTime, true, hit);
	if (Bounces < 0) {
		Destroy();
	}
	/*if (hit == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *hit->ToString());*/
	
}

void AProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	/*if (ATank* tank = Cast<ATank>(OtherActor)) {
		for (const auto& tag : TargetTags) {
			UE_LOG(LogTemp, Warning, TEXT("%s"), *tag);
			if (tank->Tags.Contains(tag) == true) {
				tank->TakeHit();
				Destroy();
				return;
			}
		}
	}*/
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{

}



