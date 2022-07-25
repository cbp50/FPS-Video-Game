// Fill out your copyright notice in the Description page of Project Settings.


#include "Lazer.h"


ALazer::ALazer() {

	reloadTime = 1.0f;
	bulletSpeed = 300.0f;
	maxAmmo = 5;
	ammoCount = 0;

	skeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Component"));
	skeletalComp->SetupAttachment(RootComponent);

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	sceneComp->SetupAttachment(RootComponent);
}

void ALazer::setAmmo(int x) {

	if (ammoCount + x <= maxAmmo) {
		ammoCount += x;
	}
	else {
		ammoCount = maxAmmo;
	}
}

void ALazer::ammoDecrement() {
	ammoCount--;
}

bool ALazer::checkAmmo()
{
	if (ammoCount > 0) {
		return true;
	}
	return false;
}
