// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeamPerks.h"
#include "Perks.h"
#include "Powers.h"
#include "Store.generated.h"

UCLASS()
class BROKENBOY_API AStore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStore();

	UPROPERTY(EditDefaultsOnly, Category = "TeamPerks")
	TSubclassOf<UTeamPerks> Technician;

	UPROPERTY(EditDefaultsOnly, Category = "TeamPerks")
	TSubclassOf<UTeamPerks> Tank;

	UPROPERTY(EditDefaultsOnly, Category = "TeamPerks")
	TSubclassOf<UTeamPerks> Leader;

	UPROPERTY(EditDefaultsOnly, Category = "TeamPerks")
	TSubclassOf<UTeamPerks> Damager;

	UPROPERTY(EditDefaultsOnly, Category = "TeamPerks")
	TSubclassOf<UTeamPerks> Scout;

	UPROPERTY(EditDefaultsOnly, Category = "Powers")
	TSubclassOf<UPowers> Sprint;

	UPROPERTY(EditDefaultsOnly, Category = "Powers")
	TSubclassOf<UPowers> DoubleJump;

	UPROPERTY(EditDefaultsOnly, Category = "Perks")
	TSubclassOf<UPerks> Shield;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
