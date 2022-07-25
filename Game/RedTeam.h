// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BROKENBOY_API RedTeam
{
public:
	RedTeam();
	~RedTeam();
	
	void addRoundWinRed();
	int getRoundWinsRed();
	void setRedKills(int k);
	int getRedKills();

private:
	int kills;
	int roundsWon;
	bool side;
};

//array of team members is something we could do.