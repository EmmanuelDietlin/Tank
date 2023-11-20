#pragma once

#include "TanksData.h"
#include "CoreMinimal.h"
#include "TankGameInstance.h"
#include "Tank.h"
#include "PlayerTank.h"
#include "EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class TANKSGAME_API AEnemyTank : public ATank
{
	GENERATED_BODY()

#pragma region Methods
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable)
	void PlaceMine();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	FRotator GetTurretRotation();
	UFUNCTION(BlueprintCallable)
	void RotateTurret(FRotator TargetRotation, double DeltaTime);
	int GetRemainingProjectileCount() override;
	void TogglePause(bool Pause) override;
#pragma endregion

#pragma region Fields
public:
	UPROPERTY(EditAnywhere, Category = "Tank")
	class UTanksData* TanksData;

	UPROPERTY(EditAnywhere, Category = "Tank")
	TEnumAsByte<TankTypes> TankType;

	UPROPERTY(BlueprintReadWrite)
	FVector NextPosition = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<APlayerTank> PlayerTank;

private:
	UTankGameInstance* TankGameInstance;
#pragma endregion
};

