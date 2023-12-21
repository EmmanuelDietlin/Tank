// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerStatusDetector.h"
#include "RawInput.h"
#include "RawInputFunctionLibrary.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "GenericPlatform/GenericPlatformInputDeviceMapper.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"

// Sets default values
AControllerStatusDetector::AControllerStatusDetector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IPlatformInputDeviceMapper::Get().GetOnInputDeviceConnectionChange().AddUObject(this, &AControllerStatusDetector::ListenForControllerChange);

}

// Called when the game starts or when spawned
void AControllerStatusDetector::BeginPlay()
{
	Super::BeginPlay();
	IRawInput* RawInput = static_cast<IRawInput*>(static_cast<FRawInputPlugin*>(&FRawInputPlugin::Get())->GetRawInputDevice().Get());

	if (RawInput != nullptr) {

		RawInput->QueryConnectedDevices();
	}
	
}

// Called every frame
void AControllerStatusDetector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AControllerStatusDetector::ListenForControllerChange(EInputDeviceConnectionState connectionState, FPlatformUserId userID, FInputDeviceId inputDeviceID)
{
	IRawInput* RawInput = static_cast<IRawInput*>(static_cast<FRawInputPlugin*>(&FRawInputPlugin::Get())->GetRawInputDevice().Get());

	RawInput->QueryConnectedDevices();

	OnControllerConnection(connectionState, userID, inputDeviceID);
}

