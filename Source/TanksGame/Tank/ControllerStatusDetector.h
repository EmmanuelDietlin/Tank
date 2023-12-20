// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControllerStatusDetector.generated.h"

UCLASS()
class TANKSGAME_API AControllerStatusDetector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AControllerStatusDetector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ListenForControllerChange(bool isConnected, FPlatformUserId UserId, int32 userId);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Controller Events")
	void OnControllerConnection(bool IsConnected);

};
