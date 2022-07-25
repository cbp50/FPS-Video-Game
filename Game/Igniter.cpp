// Fill out your copyright notice in the Description page of Project Settings.


#include "Igniter.h"

// Sets default values
AIgniter::AIgniter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIgniter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIgniter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

