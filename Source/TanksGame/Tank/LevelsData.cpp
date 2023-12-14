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

int ULevelsData::GetLevelIndex(FString LevelName) 
{
	for (int i = 0; i < LevelsData.Num(); i++) 
	{
		if (LevelsData[i].Level.GetAssetName() == LevelName)
		{
			return i;
		}
	}
	return -1;
}