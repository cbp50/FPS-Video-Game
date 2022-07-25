// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "Camera/CameraComponent.h"
#include "Weapon.h"
#include "TeamPerks.h"
#include "Perks.h"
#include "Powers.h"
#include "Assualt.h"
#include "Lazer.h"
#include "Shotgun.h"
#include "Engine/GameInstance.h"
#include "Boy.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class BROKENBOY_API ABoy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera1")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpringArmComp")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "meshComp")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "scenComp")
		USceneComponent* sceneComponent;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		AAssualt* StartingWeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		AShotgun * SecondWeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		ALazer * ThirdWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh1P")
		USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditDefaultsOnly, Category = "TeamPerks")
		TSubclassOf<UTeamPerks> TeamPower;

	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
		TSubclassOf<UPowers> Sprint;

	UPROPERTY(EditDefaultsOnly, Category = "DoubleJump")
		TSubclassOf<UPowers> DoubleJump;

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
		TSubclassOf<UPerks> Shield;


	//A UFUNCTION
	void OnRep_AttachWeapon();

		//Change to replicated on OnRep_AttachWeapon
		 AWeapon* CurrentWeapon;
		 FVector StartLocation;
		 FRotator StartRotation;
	UFUNCTION(BlueprintCallable, Category = "Plant Bomb")
	void PlantBomb();

	UFUNCTION(BlueprintCallable, Category = "Cannot Plant bomb")
	void NoPlantBomb();

	UFUNCTION(BlueprintCallable, Category = "Defuse bomb")
	void defuse();

	UFUNCTION(BlueprintCallable, Category = "Cannot Defuse Bomb")
	void NoDefuse();

	UFUNCTION(BlueprintCallable, Category = "Select Side")
		void  setAttacker(bool& side);

	UPROPERTY(EditAnywhere, Category = "Defaults")
		bool alphaTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
		bool rangeToPlant;

protected:
	// Called when the game starts or when spawned

	//movement of character
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveForward(float w);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Turn(float t);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void LookUp(float t);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveRight(float t);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	int SwitchWeapon(float t, int length, int lastIndex);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void Death();

	//UFUNCTION(BlueprintImplementable, Category = "Weapons")
		void color();


	 FAttachmentTransformRules* KeepRelativeTransform;

	
	//Death is needed
	float BaseTurnRate;
	float BaseLookUpRate;
	int laserAmmo;
	int shotgunAmmo;
	int assaultAmmo;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	bool rangeToDefuse;
	int weaponIndex;
	UMaterialInstanceDynamic * body;
	
	
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
