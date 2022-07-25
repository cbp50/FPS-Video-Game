// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Market.generated.h"

UCLASS()
class BROKENBOY_API AMarket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarket();
	
private:
	int LaserAmmo;
	int ShotgunAmmo;
	int AssaultAmmo;
	float speedBoost;
	float gunRecharge;
	int price;
	/*
	Powers
	Perks
	
	
	
	
	*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

//Purchase

//Ammo - This can be found on the map but also in the market.
  // shotgun ammo
  // lazer ammo
  

//Powers - When used it is over
  // Revival
  // shield - deflect
  

//Perks - continues throughout each round
  // wall running
  // faster speed
  // faster reload
  // double jump
