// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"

void ATankGameMode::ToggleWeaponPause(bool Pause)
{
	OnTogglePauseDelegate.Broadcast(Pause);
}

TArray<FVersusPlayerInfos> ATankGameMode::MergeSortArray(const TArray<FVersusPlayerInfos>& Array, bool Ascending)
{
	if (Array.Num() <= 1) {
		return Array;
	}

	TArray<FVersusPlayerInfos> left, right;
	int half = Array.Num() / 2;
	for (int i = 0; i < Array.Num(); i++) {
		if (i < half) left.Add(Array[i]);
		else right.Add(Array[i]);
	}

	return MergeArray(MergeSortArray(left, Ascending), MergeSortArray(right, Ascending), Ascending);

}


TArray<FVersusPlayerInfos> ATankGameMode::MergeArray(const TArray<FVersusPlayerInfos>& LeftArray, const TArray<FVersusPlayerInfos>& RightArray, bool Ascending)
{
	if (LeftArray.Num() == 0) {
		return RightArray;
	}
	if (RightArray.Num() == 0) {
		return LeftArray;
	}
	if (Ascending)
	{
		if (LeftArray[0].Score <= RightArray[0].Score)
		{
			TArray<FVersusPlayerInfos> returnArray{ LeftArray[0] };
			TArray<FVersusPlayerInfos> newLeftArray{ LeftArray };
			newLeftArray.RemoveAt(0);
			returnArray.Append(MergeArray(newLeftArray, RightArray, Ascending));
			return returnArray;
		}
		else
		{
			TArray<FVersusPlayerInfos> returnArray{ RightArray[0] };
			TArray<FVersusPlayerInfos> newRightArray{ RightArray };
			newRightArray.RemoveAt(0);
			returnArray.Append(MergeArray(LeftArray, newRightArray, Ascending));
			return returnArray;
		}
	}
	else
	{
		if (LeftArray[0].Score > RightArray[0].Score)
		{
			TArray<FVersusPlayerInfos> returnArray{ LeftArray[0] };
			TArray<FVersusPlayerInfos> newLeftArray{ LeftArray };
			newLeftArray.RemoveAt(0);
			returnArray.Append(MergeArray(newLeftArray, RightArray, Ascending));
			return returnArray;
		}
		else
		{
			TArray<FVersusPlayerInfos> returnArray{ RightArray[0] };
			TArray<FVersusPlayerInfos> newRightArray{ RightArray };
			newRightArray.RemoveAt(0);
			returnArray.Append(MergeArray(LeftArray, newRightArray, Ascending));
			return returnArray;
		}
	}
}