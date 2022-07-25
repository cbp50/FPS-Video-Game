// Fill out your copyright notice in the Description page of Project Settings.


#include "Powers.h"

// Sets default values for this component's properties
UPowers::UPowers()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PowerName = " ";
	PowerDescription = " ";
	// ...
}


// Called when the game starts
void UPowers::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPowers::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

