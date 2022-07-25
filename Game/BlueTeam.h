// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BROKENBOY_API BlueTeam
{
public:
	BlueTeam();
	~BlueTeam();

	void addRoundWinBlue();
	int getRoundWinsBlue();
	void setBlueKills(int k);
	int getBlueKills();

private:
	int kills;
	int roundsWon;
	bool side;
};

//array of team members is something we could do.