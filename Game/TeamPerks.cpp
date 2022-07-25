// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamPerks.h"

// Sets default values for this component's properties
UTeamPerks::UTeamPerks()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}


void UTeamPerks::setTeamPerkCount(int i)
{
	TeamPerkCount = i;
}

void UTeamPerks::setTeamPerkMovementCount(int i)
{
	TeamPerkMovementCount = i;
}

int UTeamPerks::getTeamPerkCount()
{
	return TeamPerkCount;
}


// Called when the game starts
void UTeamPerks::BeginPlay()
{
	Super::BeginPlay();

	Name = " ";
	TeamPerkName = " ";
	TeamPerkMovementName = " ";
	TeamPerkCount = 1;
	TeamPerkMovementCount = 1;

	// ...
	
}


// Called every frame
void UTeamPerks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

