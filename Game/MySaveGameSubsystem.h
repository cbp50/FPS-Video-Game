// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MySaveGameSubsystem.generated.h"

class UMySaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameSignature, class UMySaveGame*, SaveObject);
/**
 * 
 */
UCLASS(meta = (DisplayName = "SaveGame System"))
class BROKENBOY_API UMySaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	/* Name of slot to save/load to disk. Filled by SaveGameSettings (can be overriden from GameMode's InitGame()) */
	FString CurrentSlotName;

	UPROPERTY()
		UMySaveGame* CurrentSaveGame;

public:

	/* Restore serialized data from PlayerState into player */
	void HandleStartingNewPlayer(AController* NewPlayer);

	/* Restore spawn transform using stored data per PlayerState after being fully initialized. */
	UFUNCTION(BlueprintCallable)
		bool OverrideSpawnTransform(AController* NewPlayer);

	/* Change slot name, will be used next time we load/save data */
	UFUNCTION(BlueprintCallable)
		void SetSlotName(FString NewSlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void WriteSaveGame();

	/* Load from disk, optional slot name */
	void LoadSaveGame(FString InSlotName = "");

	UPROPERTY(BlueprintAssignable)
		FOnSaveGameSignature OnSaveGameLoaded;

	UPROPERTY(BlueprintAssignable)
		FOnSaveGameSignature OnSaveGameWritten;

	/* Initialize Subsystem, good moment to load in SaveGameSettings variables */
	void Initialize(FSubsystemCollectionBase& Collection) override;

};
