// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelsData.h"

void ULevelsData::SetDataForLevel(FString LevelName, int value) 
{
	for (auto& [key, val] : LevelsData) 
	{
		if (key.IsNull() == true) continue;
		if (key.GetAssetName() == LevelName) 
		{
			val.TanksCount = value;
			break;
		}
	}
}

FLevelData ULevelsData::GetDataForLevel(FString LevelName)
{
	for (auto& [key, val] : LevelsData)
	{
		if (key.IsNull() == true) continue;
		if (key.GetAssetName() == LevelName)
		{
			return val;
		}
	}
	return FLevelData();
}