// Copyright Epic Games, Inc. All Rights Reserved.


#include "BrokenBoyGameModeBase.h"
#include "Boy.h"
#include "DefusionGameStateBase.h"
#include "BrokenBoy.h"
#include "Engine/World.h"
#include "BoyController.h"
#include "MyInterface.h"
#include "MySaveGameSubsystem.h"
#include "MySaveGameSettings.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Engine/DataTable.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <Runtime/CoreUObject/Public/Serialization/ObjectAndNameAsStringProxyArchive.h>
#include <BrokenBoy/MyInterface.h>



ABrokenBoyGameModeBase::ABrokenBoyGameModeBase() {
	static ConstructorHelpers::FClassFinder<ABoy> PlayerPawnClassFinder(TEXT("/Game/Player-Character-Blueprint/MyBoy1"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	GameStateClass = ADefusionGameStateBase::StaticClass();
	PlayerControllerClass = ABoyController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	numTeamA = 0;
	numTeamB = 0;
	
	SlotName = "SaveGame4";
	
}

void ABrokenBoyGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);


	FString SelectedSaveSlot = UGameplayStatics::ParseOption(Options, "SaveGame2");
	if (SelectedSaveSlot.Len() > 0)
	{
		SlotName = SelectedSaveSlot;
	}
	rounds = 0;
	LoadSaveGame();
	
}

void ABrokenBoyGameModeBase::BeginPlay() {
	Super::BeginPlay();




	if (CurrentSaveGame->GameSaveData.rounds > 3) {
		CurrentSaveGame->GameSaveData.rounds = 0;
	}

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Purple, FString::Printf(TEXT("Bool: %s"), GetWorld()->IsMapChangeReady() ? TEXT("true") : TEXT("false")));

}
//Needs work: A little confusing between attacking and teams. Sides and Teams.


void ABrokenBoyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "PostLoginStart");
	if (NewPlayer) {
		AMyPlayerState* PS = Cast<AMyPlayerState>(NewPlayer->PlayerState);

		uint8 NumTeamA = 0;
		uint8 NumTeamB = 0;

		if (PS && GameState) {

			//something could be wrong here

			for (APlayerState* It : GameState->PlayerArray) {

				AMyPlayerState* otherPS = Cast<AMyPlayerState>(It);
				if (otherPS) {

					if (otherPS->alphaTeam) {
						NumTeamB++;
						GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, "NumB");

					}
					else {
						NumTeamA++;
						GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, "NumA");
					}
				}

			}

		}
		if (NumTeamA > NumTeamB) {
			// Doesn't actuatlly change value.
			PS->alphaTeam = true;

			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("Bool: %s"), PS->getAttacker() ? TEXT("true") : TEXT("false")));
		}
	}

}


void ABrokenBoyGameModeBase::switchSides()
{
	
	TArray<AActor*> PlayerStarts;
	TSubclassOf<APlayerStart> PlayerStart = APlayerStart::StaticClass();
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), PlayerStart, "Attacker", PlayerStarts);
		for (auto i : PlayerStarts){
			Cast<APlayerStart>(i)->Tags[0] == "Blue";
		}

		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), PlayerStart, "Defender", PlayerStarts);
		for (auto i : PlayerStarts) {
			Cast<APlayerStart>(i)->Tags[0] == "Red";
		}
}


void ABrokenBoyGameModeBase::GameOver() {
	//1. ScoreBoard
	//2. Take everyone to lobby
	
	CurrentSaveGame->GameSaveData.rounds = 0;
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, "GameOver");
	
}


void ABrokenBoyGameModeBase::RoundOver() {
	//A series of steps going into the next round

	rounds++;
	//saveRounds();
	if (rounds == 3) {
		GameOver();
	}
	
	UGameplayStatics::OpenLevel(GetWorld(), "Demo-Animations");
	UE_LOG(LogTemp, Warning, TEXT("New World"));
	UE_LOG(LogTemp, Warning, TEXT("Round Number: %d"), rounds);
	LoadSaveGame();
	WriteSaveGame();
	switchSides();

	//1. ScoreBoard
	//2. Switch Sides
	//3. Start the game again.

}

void ABrokenBoyGameModeBase::WriteSaveGame()
{
	
	// Clear arrays, may contain data from previously loaded SaveGame
	
		CurrentSaveGame->SavedPlayers.Empty();
		CurrentSaveGame->SavedActors.Empty();

	
	// Iterate all player states, we don't have proper ID to match yet (requires Steam or EOS)
	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		
		AMyPlayerState* PS = Cast<AMyPlayerState>(GameState->PlayerArray[i]);
		if (PS)
		{
			PS->SavePlayerState(CurrentSaveGame);
			break; // single player only at this point
		}
	}


	
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		// Only interested in our 'gameplay actors'
		if (!Actor->Implements<UMyInterface>())
		{
			continue;
		}

		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetFName();
		ActorData.Transform = Actor->GetActorTransform();

		// Pass the array to fill with data from Actor
		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		// Find only variables with UPROPERTY(SaveGame)
		Ar.ArIsSaveGame = true;
		// Converts Actor's SaveGame UPROPERTIES into binary array
		Actor->Serialize(Ar);

		CurrentSaveGame->SavedActors.Add(ActorData);
	}
	
	CurrentSaveGame->GameSaveData.rounds = rounds;
	UE_LOG(LogTemp, Warning, TEXT("Save round is %d"), rounds);
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);

	OnSaveGameWritten.Broadcast(CurrentSaveGame);
}



void ABrokenBoyGameModeBase::checkKills()
{

	if (defusionGameState->getRedTeamMembersLeft() == 0 || defusionGameState->getBlueTeamMembersLeft() == 0) {
		RoundOver();
	}

}




void ABrokenBoyGameModeBase::initTeams()
{
	for (APlayerState* It : GameState->PlayerArray) {

		AMyPlayerState* PS = Cast<AMyPlayerState>(It);
		if (PS->alphaTeam && numTeamA <= 5) {
			numTeamA++;
		}
		else if (PS->DeltaTeam && numTeamB <= 5) {
			numTeamB++;
		}
	}

}

void ABrokenBoyGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	// Calling Before Super:: so we set variables before 'beginplayingstate' is called in PlayerController (which is where we instantiate UI)
	AMyPlayerState* PS = NewPlayer->GetPlayerState<AMyPlayerState>();
	if (ensure(PS))
	{
		PS->LoadPlayerState(CurrentSaveGame);
	}

	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	// Now we're ready to override spawn location
	// Alternatively we could override core spawn location to use store locations immediately (skipping the whole 'find player start' logic)
//	if (PS)
//	{
//		PS->OverrideSpawnTransform(CurrentSaveGame);
//	}

}

AActor* ABrokenBoyGameModeBase::ChoosePlayerStart_Implementation(AController* player) {

	//Team color: add a team bool.
	Super::ChoosePlayerStart_Implementation(player);
	TArray<AActor*> PlayerStarts;
	PlayerControllerClass = ABoyController::StaticClass();
	TSubclassOf<APlayerStart> PlayerStart = APlayerStart::StaticClass();
	playerController = Cast<ABoyController>(player);
	playerState = Cast<AMyPlayerState>(player->PlayerState);
	

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("Bool: %s"), playerState->getAttacker() ? TEXT("true") : TEXT("false")));
	if (playerState->getAttacker()) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Attacker");
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), PlayerStart, "Attacker", PlayerStarts);
		playerState->sides = "Attacker";
		for (auto i : PlayerStarts) {
			if (Cast<APlayerStart>(i)->PlayerStartTag != "Taken") {
				Cast<APlayerStart>(i)->PlayerStartTag = "Taken";
				return i;
			}
		}

	}
	else if (!playerState->getAttacker()) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Defender");
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), PlayerStart, "Defender", PlayerStarts);
		playerState->sides = "Defender";
		for (auto i : PlayerStarts) {
			if (Cast<APlayerStart>(i)->PlayerStartTag != "Taken") {
				Cast<APlayerStart>(i)->PlayerStartTag = "Taken";
				return i;
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "No Team");
	
	return Super::ChoosePlayerStart_Implementation(player);
}

//Change to playerState
void ABrokenBoyGameModeBase::kill(ABoy* boy)
{
	 defusionGameState = Cast<ADefusionGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	AController* boy1 = boy->GetController();
	if (boy1->ActorHasTag("Red")) {
		controller = boy1;
		controller->UnPossess();
		defusionGameState->RedTeamDeath();
		
	}
	else if (boy1->ActorHasTag("Blue")) {
		controller = boy1;
		controller->UnPossess();
		defusionGameState->BlueTeamDeath();
	}
}

void ABrokenBoyGameModeBase::setAttacker(bool& side)
{
	side = true;
}

void ABrokenBoyGameModeBase::LoadSaveGame()
{


	
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{

		UE_LOG(LogTemp, Warning, TEXT("Existing SaveGame Data."));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Loading");
		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (CurrentSaveGame->GameSaveData.rounds >= 3) {
			CurrentSaveGame->GameSaveData.rounds = 0;
		}

		if (CurrentSaveGame == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));

		// Iterate the entire world of actors
		for (FActorIterator It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;
			// Only interested in our 'gameplay actors'
			if (!Actor->Implements<UMyInterface>())
			{
				continue;
			}

			for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
			{
				if (ActorData.ActorName == Actor->GetFName())
				{
					Actor->SetActorTransform(ActorData.Transform);

					FMemoryReader MemReader(ActorData.ByteData);

					FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
					Ar.ArIsSaveGame = true;
					// Convert binary array back into actor's variables
					Actor->Serialize(Ar);

					IMyInterface::Execute_OnActorLoaded(Actor);

					break;
				}
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Load round is %d"), rounds);
		CurrentSaveGame->GameSaveData.rounds++;
		UE_LOG(LogTemp, Warning, TEXT("Load save round is %d"), CurrentSaveGame->GameSaveData.rounds);
		rounds = CurrentSaveGame->GameSaveData.rounds;
		OnSaveGameLoaded.Broadcast(CurrentSaveGame);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("round is %d"), rounds);
		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		UE_LOG(LogTemp, Log, TEXT("Created New SaveGame Data."));
	}

}