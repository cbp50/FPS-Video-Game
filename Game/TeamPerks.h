// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Texture2D.h"
#include "TeamPerks.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROKENBOY_API UTeamPerks : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeamPerks();
	FString Name; // For when player buys
	FString TeamPerkName; // Compare to run animation
	FString TeamPerkMovementName; // Compare to run animation

	FString TeamPerkDescription;
	FString TeamPerkMovementDescription;
	UTexture2D* texture2D;
	
	void setTeamPerkCount(int);
	void setTeamPerkMovementCount(int);
	int getTeamPerkCount();
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	int TeamPerkCount;
	int TeamPerkMovementCount;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
