// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseDelegate, bool, Pause);
/**
 * 
 */
UCLASS()
class TANKSGAME_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FPauseDelegate OnTogglePauseDelegate;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleWeaponPause(bool Pause);
	UFUNCTION(BlueprintCallable)
	TArray<FVersusPlayerInfos> MergeSortArray(const TArray<FVersusPlayerInfos>& Array, bool Ascending);

private:
	TArray<FVersusPlayerInfos> MergeArray(const TArray<FVersusPlayerInfos>& LeftArray, const TArray<FVersusPlayerInfos>& RightArray, bool Ascending);
	
};
