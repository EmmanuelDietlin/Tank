// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerData.h"

FMapData UMultiplayerData::GetMapData(EMapType MapType, int Index) {
	switch (MapType)
	{
	case EMapType::CoopMapType:
		if (Index < 0 || Index >= CoopMapsList.Num())
			return FMapData();
		return CoopMapsList[Index];
	case EMapType::VersusMapType:
		if (Index < 0 || Index >= VersusMapsList.Num())
			return FMapData();
		return VersusMapsList[Index];
	default:
		return FMapData();
	}
}

int UMultiplayerData::GetMapListSize(EMapType MapType) {
	switch (MapType) 
	{
	case EMapType::CoopMapType:
		return CoopMapsList.Num();
	case EMapType::VersusMapType:
		return VersusMapsList.Num();
	default:
		return 0;
	}
}