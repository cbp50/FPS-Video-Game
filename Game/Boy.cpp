// Fill out your copyright notice in the Description page of Project Settings.


#include "Boy.h"
#include "GameFramework/SpringArmComponent.h"
#include "Assualt.h"
#include "Lazer.h"
#include "Shotgun.h"
#include "DefusionGameStateBase.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ABoy::ABoy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	sceneComponent->SetupAttachment(RootComponent);

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	Mesh1P->SetupAttachment(sceneComponent);

	/*CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(sceneComponent);
	CameraComp->bUsePawnControlRotation = true;
	*/


	weaponIndex = 0;

	laserAmmo = 0;
	shotgunAmmo = 0;
	assaultAmmo = 0;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;
	rangeToPlant = false;
	rangeToDefuse = false;

}
void ABoy::Death()
{
	ABrokenBoyGameModeBase* GameMode = (ABrokenBoyGameModeBase *)GetWorld()->GetAuthGameMode();
	GameMode->kill(this);
	Destroy();
	
}
void ABoy::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {

	}
	/*if (HasAuthority()) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(StartingWeaponClass, SpawnParams);
		if (CurrentWeapon) {
			UE_LOG(LogTemp, Warning, TEXT("SPAWNED AND ATTEMEPTED TO ATTACH WEAPON TO HAND"));
			OnRep_AttachWeapon();
		}
		if (AWeapon* weapon1 = GetWorld()->SpawnActor<AWeapon>(SecondWeaponClass, SpawnParams)) {
			weapon1->SetHidden(true);
			weapon1->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Bone_013_R"));
		}

		if (AWeapon* ResultPawn = SpawnActor<AWeapon>(D, StartLocation, StartRotation, NULL, GetInstigator())) {
			weapon1->SetHidden(true);
			weapon1->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Bone_013_R"));
		}
	}
	*/
	
}





void ABoy::MoveForward(float w)
{

	
	if ((Controller) && (w != 0.0f)) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, w);
	}
}

void ABoy::Turn(float t)
{
	AddControllerYawInput(t * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABoy::LookUp(float t)
{
	AddControllerPitchInput(t * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void ABoy::MoveRight(float t)
{
	if ((Controller) && (t != 0.0f)) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, t);
	}
}

// Called when the game starts or when spawned

// Called every frame
void ABoy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoy::OnRep_AttachWeapon()
{
	if (CurrentWeapon) {

		if (true || IsLocallyControlled()) {
			CurrentWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Bone_013_R"));
			
		}
		else {
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Bone_013_R"));
			
		}

	}
}

void ABoy::PlantBomb() {
	rangeToPlant = true;
}

void ABoy::NoPlantBomb()
{
	rangeToPlant = false;
}


int ABoy::SwitchWeapon(float t, int length, int lastIndex) {
	UE_LOG(LogTemp, Warning, TEXT("Switching to Next Weapon"));
	if (t > 0.0) {
		weaponIndex++;
		weaponIndex = weaponIndex % length;
		return weaponIndex;
	}
	else if (t < 0.0) {

		UE_LOG(LogTemp, Warning, TEXT("Switching to Previous Weapon"));

		weaponIndex--;
		if (weaponIndex < 0) {
			return lastIndex;
		}
		else {
			return weaponIndex;
		}
	}
	return 0;
	
}




// Called to bind functionality to input
void ABoy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//PlayerInputComponent->BindAction("PlantBomb", IE_Pressed, this, &ABoy::SetActive);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABoy::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABoy::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABoy::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ABoy::Turn);

	
}

void ABoy::color() {

	body = Mesh1P->CreateDynamicMaterialInstance(1, NULL, "None");
	
}

void ABoy::defuse()
{
	
	rangeToDefuse = true;

}
void ABoy::NoDefuse()
{

	rangeToDefuse = false;

}

void ABoy::setAttacker(bool& side)
{
	side = true;
}

