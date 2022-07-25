// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "Boy.h"
#include "BrokenBoyGameModeBase.h"
#include "DefusionGameStateBase.h"
#include "Components/BoxComponent.h"
#include "MyPlayerState.h"
#include "NewBomb.generated.h"

class UBoxComponent;

UCLASS()
class BROKENBOY_API ANewBomb : public AActor, public IMyInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float TargetPitch;

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

	void Interact_Implementation(APawn* InstigatorPawn);

	void OnActorLoaded_Implementation();

protected:
	UPROPERTY(ReplicatedUsing = "OnRep_VideoHatchOpened", BlueprintReadOnly, SaveGame) // RepNotify
		bool bVideoHatchOpened;

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnRep_VideoHatchOpened();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* LidMesh;

public:
	// Sets default values for this actor's properties
	ANewBomb();

private:
	bool timeElapsed;
	bool  activated;
	bool  deactivated;
	AMyPlayerState* playerState;
	ABoy* player;
};