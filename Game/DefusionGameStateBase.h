// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BrokenBoyGameModeBase.h"
#include "NewBomb.h"
#include "DefusionGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BROKENBOY_API ADefusionGameStateBase : public AGameState
{
	GENERATED_BODY()

public:
		ADefusionGameStateBase();
		ADefusionGameStateBase(int red, int blue);
		
		void addRoundWinBlue();
		void addRoundWinRed();
		int getRoundWinsBlue();
		int getRoundWinsRed();

		void BlueTeamDeath();
		void RedTeamDeath();
		int getRedTeamMembersLeft();
		int getBlueTeamMembersLeft();
	

		FTimerHandle TimeHandle;

		UFUNCTION(BlueprintCallable, Category = "Timer Function")
		void TimerFunction();

		UFUNCTION(BlueprintCallable, Category = "Bomb activated")
		void BombActivated();

		UFUNCTION(BlueprintCallable, Category = "Bomb defused")
		void Defused();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "active")
		bool active;

		double bombTimer;

private:
	bool blueTeam;
	bool redTeam;
	int redWins;
	int blueWins;
	int blueTeamLeft;
	int redTeamLeft;
	bool endMatch;
	
};
