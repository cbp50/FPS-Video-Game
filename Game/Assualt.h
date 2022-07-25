// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Assualt.generated.h"

/**
 * 
 */



UCLASS()
class BROKENBOY_API AAssualt : public AWeapon
{
	GENERATED_BODY()

public:
	AAssualt();

	UFUNCTION(BlueprintCallable, Category = "set Ammo")
		void setAmmo(int x);

	UFUNCTION(BlueprintCallable, Category = "ammo Decrement")
		void ammoDecrement();

	UFUNCTION(BlueprintCallable, Category = "check ammo")
		bool checkAmmo();

	
	
};
