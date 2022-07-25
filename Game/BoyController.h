// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BoyController.generated.h"

/**
 * 
 */
UCLASS()
class BROKENBOY_API ABoyController : public APlayerController
{
	GENERATED_BODY()
public:
	ABoyController();
	bool attacker;
	bool defender;
	FName red;
	FName blue;

private:
	
	
};
