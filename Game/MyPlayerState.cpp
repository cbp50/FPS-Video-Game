// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "MySaveGame.h"
#include "Net/UnrealNetwork.h"

AMyPlayerState::AMyPlayerState() {
	
	bomb = true;
	attacker = true;
}

bool AMyPlayerState::HasBomb() {
	return bomb;
}

void AMyPlayerState::setAttacker(bool & side)
{
	attacker = true;
}

void AMyPlayerState::PickedBomb()
{
	 bomb = true; 
}

bool AMyPlayerState::getAttacker() {
	return attacker; 
}

void AMyPlayerState::SavePlayerState_Implementation(UMySaveGame* SaveObject)
{
	if (SaveObject)
	{
		// Gather all relevant data for player
		FPlayerSaveData SaveData;
		SaveData.kills = Kills;
		SaveData.deaths = Deaths;
		SaveData.PersonalRecordTime = PersonalRecordTime;
		// Stored as FString for simplicity (original Steam ID is uint64)
		SaveData.PlayerID = GetUniqueId().ToString();

		// May not be alive while we save
		if (APawn* MyPawn = GetPawn())
		{
			SaveData.Location = MyPawn->GetActorLocation();
			SaveData.Rotation = MyPawn->GetActorRotation();
			SaveData.bResumeAtTransform = true;
		}

		SaveObject->SavedPlayers.Add(SaveData);
	}
}


void AMyPlayerState::LoadPlayerState_Implementation(UMySaveGame* SaveObject)
{
	if (SaveObject)
	{
		FPlayerSaveData* FoundData = SaveObject->GetPlayerData(this);
		if (FoundData)
		{
			//Credits = SaveObject->Credits;
			// Makes sure we trigger credits changed event
			
			AddKills(FoundData->kills);
			AddKills(FoundData->deaths);

			PersonalRecordTime = FoundData->PersonalRecordTime;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not find SaveGame data for player id '%i'."), GetPlayerId());
		}
	}
}

void AMyPlayerState::AddKills(int32 Delta)
{
	// Avoid user-error of adding a negative amount
	if (!ensure(Delta >= 0.0f))
	{
		return;
	}

	Kills += Delta;

	OnCreditsChanged.Broadcast(this, Kills, Delta);
}

void AMyPlayerState::AddDeaths(int32 Delta)
{
	// Avoid user-error of adding a negative amount
	if (!ensure(Delta >= 0.0f))
	{
		return;
	}

	Deaths += Delta;

	OnCreditsChanged.Broadcast(this, Deaths, Delta);
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, Kills);
	DOREPLIFETIME(AMyPlayerState, Deaths);
}

void AMyPlayerState::OnRep_Kills(int32 OldKills)
{
	OnCreditsChanged.Broadcast(this, Kills, Kills - OldKills);
}

void AMyPlayerState::OnRep_Deaths(int32 OldDeaths)
{
	OnCreditsChanged.Broadcast(this, Deaths, Deaths - OldDeaths);
}
