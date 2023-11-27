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
	case EMapType::CampaignMapType:
		if (Index < 0 || Index >= CampaignMapsList.Num())
			return FMapData();
		return CampaignMapsList[Index];
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
	case EMapType::CampaignMapType:
		return CampaignMapsList.Num();
	default:
		return 0;
	}
}