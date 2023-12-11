// Fill out your copyright notice in the Description page of Project Settings.


#include "CampaignGameState.h"
#include "Net/UnrealNetwork.h"


void ACampaignGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACampaignGameState, Score);
	DOREPLIFETIME(ACampaignGameState, Lives);
	DOREPLIFETIME(ACampaignGameState, RemainingEnemyTanks);
	DOREPLIFETIME(ACampaignGameState, LevelNumber);
}
