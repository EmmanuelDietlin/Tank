// Fill out your copyright notice in the Description page of Project Settings.


#include "TankSaveGame.h"
#include "Kismet/GameplayStatics.h"

UTankSaveGame::UTankSaveGame() 
{
	UserIndex = 0;
	SaveSlotName = TEXT("TestSaveSlot");
}