// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class USceneComponent;
class USkeletalMeshComponent;

UCLASS()
class BROKENBOY_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Muzzle")
	USceneComponent* sceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Mesh")
	USkeletalMeshComponent* skeletalComp;

	UFUNCTION(BlueprintImplementableEvent, Category = "fire")
	void fire(FRotator r);

	UFUNCTION(BlueprintImplementableEvent, Category = "Reload")
	void reload();

	

protected:
	// Called when the game starts or when spawned
	int maxAmmo;
	int ammoCount;
	float bulletSpeed;
	float reloadTime;
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
