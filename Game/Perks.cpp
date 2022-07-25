// Fill out your copyright notice in the Description page of Project Settings.


#include "Perks.h"

// Sets default values for this component's properties
UPerks::UPerks()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	count = 1;
	PerkName = " ";
	PerkDescription = " ";
	

	// ...
}


void UPerks::setPerkCount(int i)
{
	count = i;
}

int UPerks::getPerkCount()
{
	return count;
}

// Called when the game starts
void UPerks::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPerks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

