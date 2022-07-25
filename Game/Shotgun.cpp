// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"

AShotgun::AShotgun() {

	reloadTime = 0.8f;
	bulletSpeed = 500.0f;
	maxAmmo = 8;
	ammoCount = 0;

	skeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Component"));
	skeletalComp->SetupAttachment(RootComponent);

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	sceneComp->SetupAttachment(RootComponent);



}

void AShotgun::setAmmo(int x) {

	if (ammoCount + x <= maxAmmo) {
		ammoCount += x;
	}
	else {
		ammoCount = maxAmmo;
	}

}

void AShotgun::ammoDecrement() {
	ammoCount -= 2;
}

bool AShotgun::checkAmmo() {
	if (ammoCount > 0) {
		return true;
	}
	return false;
}