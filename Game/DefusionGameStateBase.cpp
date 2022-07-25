// Fill out your copyright notice in the Description page of Project Settings.


#include "DefusionGameStateBase.h"
#include "TimerManager.h"
#include "NewBomb.h"
#include "Kismet/GameplayStatics.h"
#include "BrokenBoyGameModeBase.h"



ADefusionGameStateBase::ADefusionGameStateBase(){

	blueTeamLeft = 5;
	redTeamLeft = 5;
	active = false;
	bombTimer = 45.0;
}

ADefusionGameStateBase::ADefusionGameStateBase(int red, int blue) {

	active = false;
	blueTeamLeft = 5;
	redTeamLeft = 5;
	redWins = red;
	blueWins = blue;
	bombTimer = 45.0;

}

void ADefusionGameStateBase::addRoundWinBlue() {
	blueWins++;
}

void ADefusionGameStateBase::addRoundWinRed() {
	redWins++;
}

int ADefusionGameStateBase::getRoundWinsBlue() {
	return blueWins;
}

int ADefusionGameStateBase::getRoundWinsRed() {
	return redWins;
}

void ADefusionGameStateBase::BlueTeamDeath(){
	blueTeamLeft--;
}

void ADefusionGameStateBase::RedTeamDeath(){
	redTeamLeft--;
}

int ADefusionGameStateBase::getRedTeamMembersLeft(){
	return redTeamLeft;
}

int ADefusionGameStateBase::getBlueTeamMembersLeft(){
	return blueTeamLeft;
}


void ADefusionGameStateBase::TimerFunction() {
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "TimerFunction Has Begun");
	active = true;
	GetWorldTimerManager().SetTimer(TimeHandle, this, &ADefusionGameStateBase::BombActivated, 5.0f, false);
	
}


void  ADefusionGameStateBase::BombActivated(){

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "BombActivated Has Begun");
	ABrokenBoyGameModeBase* gameMode = Cast<ABrokenBoyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (active == false) {
		GetWorldTimerManager().ClearTimer(TimeHandle);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "active is false");
		gameMode->RoundOver();
		

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOM");
		gameMode->RoundOver();
		

	}
	
}

void ADefusionGameStateBase::Defused()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Atempting to defuse");
	active = false;
}
