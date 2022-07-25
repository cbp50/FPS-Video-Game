// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Lazer.generated.h"

/**
 * 
 */
UCLASS()
class BROKENBOY_API ALazer : public AWeapon
{
	GENERATED_BODY()
	
public:

	ALazer();
	

	UFUNCTION(BlueprintCallable, Category = "set Ammo")
		void setAmmo(int x);

	UFUNCTION(BlueprintCallable, Category = "ammo Decrement")
		void ammoDecrement();

	UFUNCTION(BlueprintCallable, Category = "check ammo")
		bool checkAmmo();

};
