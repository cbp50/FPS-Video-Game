// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Boy.h"
#include "BoyController.h"
#include "GameFramework/PlayerController.h"
#include "DefusionGameStateBase.h"
#include <BrokenBoy/MyPlayerState.h>
#include "Engine/World.h"
#include <BrokenBoy/MySaveGame.h>
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Engine/DataTable.h"
#include "MySaveGameSubsystem.h"
#include "BrokenBoyGameModeBase.generated.h"





/**
 * 
 */
UCLASS()
class BROKENBOY_API ABrokenBoyGameModeBase : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABrokenBoyGameModeBase();
	virtual ~ABrokenBoyGameModeBase() = default;
	
	AActor* ChoosePlayerStart_Implementation(AController* player) override;
	void switchSides();

	UFUNCTION(BlueprintCallable, Category = "Game Over")
	void GameOver();
	UFUNCTION(BlueprintCallable, Category = "Round Over")
	void RoundOver();

	void WriteSaveGame();

	
	void checkKills();
	void BeginPlay() override;
	void PostLogin(APlayerController* NewPlayer) override;


	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	void initTeams();

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
	void kill(class ABoy * Boy);

	ADefusionGameStateBase* defusionGameState;
	bool alpha;

	UFUNCTION(BlueprintCallable, Category = "Select Side")
		void  setAttacker(bool& side);

	void LoadSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "rounds")
	int32 rounds;

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnSaveGameLoaded;

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnSaveGameWritten;
	
private:
	//init several static vars;
	
	AController* controller;
	AMyPlayerState* playerState;
	ABoyController* playerController;
	int numTeamA;
	int numTeamB;
	FName MainMap;
	FName subMap;
	UMySaveGame* saveGame;
	UMySaveGame* loadGame;
	UMySaveGame* CurrentSaveGame;
	FString SlotName;


};
