// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrokenBoyGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Boy.h"
#include "MyPlayerState.h"
#include "Bomb.generated.h"


// input
// update gamestate by game mode
// set timer

class UBoxComponent;
class USkeletalMeshComponent;
class UABoy;

UCLASS()
class BROKENBOY_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

		void static activate(bool &active);
		void static defuse(bool &active);

	ABoy* Boy;
	FTimerHandle TimeHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "activate")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb Mesh")
	USkeletalMeshComponent* skeletalMesh;

	UFUNCTION()
	void onOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void onOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool timeElapsed;
	bool  activated;
	bool  deactivated;
	AMyPlayerState* playerState;
	ABoy* player;
};
