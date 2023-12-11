// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TankGameResolutions.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TANKSGAME_API UTankGameResolutions : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TArray<FIntPoint> Resolutions;
};

