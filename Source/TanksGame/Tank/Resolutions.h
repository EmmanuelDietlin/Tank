// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Resolutions.generated.h"

/**
 * 
 */
UCLASS()
class TANKSGAME_API UResolutions : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TArray<FIntPoint> Resolutions;
};
