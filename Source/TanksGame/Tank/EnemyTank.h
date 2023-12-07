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
	UFUNCTION(Server, Reliable)
	void HandlePlaceMine();
	UFUNCTION(Server, Reliable)
	void HandleFire();
	void HandleTakeHit_Implementation(AActor* SourceActor) override;
	;
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

	UFUNCTION(BlueprintCallable)
	void SetPlayersArray(TArray<APlayerTank*> Players);
	UFUNCTION(BlueprintCallable)
	void AddPlayerToArray(APlayerTank* Player);
	UFUNCTION(BlueprintCallable)
	void RemovePlayerFromArray(APlayerTank* Player);
	UFUNCTION(BlueprintCallable)
	void RemovePlayerFromArrayAtIndex(int Index);
	UFUNCTION(BlueprintCallable)
	void ClearPlayersArray();
	UFUNCTION(BlueprintCallable)
	APlayerTank* GetPlayerFromArray(int Index);
	UFUNCTION(BlueprintCallable)
	APlayerTank* GetRandomPlayerFromArray();
	UFUNCTION(BlueprintCallable)
	APlayerTank* GetClosestPlayerFromArray();
	UFUNCTION(BlueprintCallable)
	int GetPlayersArrayLength();
	UFUNCTION(BlueprintCallable)
	void UpdatePlayersArray();
#pragma endregion

#pragma region Fields
public:
	UPROPERTY(EditAnywhere, Category = "Tank")
	class UTanksData* TanksData;

	UPROPERTY(EditAnywhere, Category = "Tank")
	TEnumAsByte<TankTypes> TankType;

	UPROPERTY(BlueprintReadWrite)
	FVector NextPosition = FVector::ZeroVector;

private:
	UTankGameInstance* TankGameInstance;
	TArray<TWeakObjectPtr<APlayerTank>> PlayerTanks;
#pragma endregion
};

