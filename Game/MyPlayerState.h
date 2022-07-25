// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */

class AMyPlayerState; // Forward declared to satisfy the delegate macros below
class UMySaveGame;

// Event Handler for Credits
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, AMyPlayerState*, PlayerState, int32, NewCredits, int32, Delta);
// Event Handler for Personal Record Time
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRecordTimeChanged, AMyPlayerState*, PlayerState, float, NewTime, float, OldRecord);



UCLASS()
class BROKENBOY_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMyPlayerState();
	//replicate
	//We need to get team color in here and which side(attacker and defender)
	UFUNCTION(BlueprintCallable, Category = "Select Side")
	void  setAttacker(bool &side);

	UFUNCTION(BlueprintCallable, Category = "Bomb picked up")
	void PickedBomb();

	UFUNCTION(BlueprintCallable, Category = "Get attacker")
	bool getAttacker();

	UFUNCTION(BlueprintCallable, Category = "Bomb picked up")
	bool HasBomb();
	
	UPROPERTY(EditAnywhere, Category = "Teams")
	bool alphaTeam;

	UPROPERTY(EditAnywhere, Category = "Teams")
	bool DeltaTeam;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,  Category = "Sides")
	FString sides;

	UFUNCTION(BlueprintNativeEvent)
		void SavePlayerState(UMySaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
		void LoadPlayerState(UMySaveGame* SaveObject);


	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnCreditsChanged OnCreditsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnRecordTimeChanged OnRecordTimeChanged;


	UFUNCTION(BlueprintCallable, Category = "Kills")
		void AddKills(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Deaths")
		void AddDeaths(int32 Delta);


private:
	bool attacker;
	bool bomb;

protected:
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = "OnRep_Kills", Category = "Kills")
		int32 Kills;
	
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = "OnRep_Deaths", Category = "Deaths")
		int32 Deaths;


	UPROPERTY(BlueprintReadOnly)
		float PersonalRecordTime;

	UFUNCTION()
		void OnRep_Kills(int32 OldKills);

	UFUNCTION()
		void OnRep_Deaths(int32 OldDeaths);


};
