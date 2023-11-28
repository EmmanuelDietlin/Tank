// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"

void ATankGameMode::ToggleWeaponPause(bool Pause)
{
	OnTogglePauseDelegate.Broadcast(Pause);
}