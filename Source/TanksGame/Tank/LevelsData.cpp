// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelsData.h"

void ULevelsData::SetDataForLevel(FString LevelName, int value) 
{
	for (auto& it : LevelsData) 
	{
		if (it.Level.GetAssetName() == LevelName) 
		{
			it.TanksCount = value;
			break;
		}
	}
}

FLevelData ULevelsData::GetDataForLevel(FString LevelName)
{
	for (auto& it : LevelsData)
	{
		if (it.Level.GetAssetName() == LevelName)
		{
			return it;
		}
	}
	return FLevelData();
}