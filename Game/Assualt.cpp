// Fill out your copyright notice in the Description page of Project Settings.


#include "Assualt.h"

AAssualt::AAssualt() {

	reloadTime = 0.8f;
	bulletSpeed = 500.0f;
	maxAmmo = 8;
	ammoCount = 8;

	skeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Component"));
	skeletalComp->SetupAttachment(RootComponent);

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	sceneComp->SetupAttachment(RootComponent);

	
}

void AAssualt::setAmmo(int x) {
	
	if (ammoCount + x <= maxAmmo) {
		ammoCount += x;
	}
	else {
		ammoCount = maxAmmo;
	}
	
}

void AAssualt::ammoDecrement() {
	ammoCount--;
}

bool AAssualt::checkAmmo() {
	if (ammoCount > 0) {
		return true;
	}
	return false;
}

