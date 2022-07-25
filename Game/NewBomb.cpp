// Fill out your copyright notice in the Description page of Project Settings.


#include "NewBomb.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>


void ANewBomb::onOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Also we need to check if Boy has the bomb
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Purple, FString::Printf(TEXT("Bool: %s"), GetWorld()->IsMapChangeReady() ? TEXT("true") : TEXT("false")));
	if (OtherActor->ActorHasTag("Attacker")) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap");
		player = Cast<ABoy>(OtherActor);
		playerState = Cast<AMyPlayerState>(player->GetPlayerState());
		Boy = Cast<ABoy>(OtherActor);
		if (playerState->sides == "Attacker" && playerState->HasBomb()) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Can Plant Bomb");
			Boy->rangeToPlant = true;
			UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Bool is %s"), (player->rangeToPlant ? TEXT("True") : TEXT("False")));
		}
	}
	else if (OtherActor->ActorHasTag("Defender")) {
		Boy = Cast<ABoy>(OtherActor);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Can Defuse");
		Boy->defuse();
	}
}

void ANewBomb::onOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	// Also we need to check if Boy has the bomb
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Purple, FString::Printf(TEXT("Bool: %s"), GetWorld()->IsMapChangeReady() ? TEXT("true") : TEXT("false")));
	if (OtherActor->ActorHasTag("Attacker")) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap");
		player = Cast<ABoy>(OtherActor);
		playerState = Cast<AMyPlayerState>(player->GetPlayerState());
		Boy = Cast<ABoy>(OtherActor);
		if (playerState->sides == "Atacker" && playerState->HasBomb()) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Cannot Plant Bomb");
			Boy->rangeToPlant = false;
		}
	}
	else if (OtherActor->ActorHasTag("Defender")) {
		Boy = Cast<ABoy>(OtherActor);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Cannot Defuse");
		Boy->NoDefuse();
	}

}

void ANewBomb::Interact_Implementation(APawn* InstigatorPawn)
{
	bVideoHatchOpened = !bVideoHatchOpened;
	OnRep_VideoHatchOpened();
}

void ANewBomb::OnActorLoaded_Implementation()
{
	OnRep_VideoHatchOpened();
}

void ANewBomb::BeginPlay()
{
	Super::BeginPlay();
}

void ANewBomb::OnRep_VideoHatchOpened()
{
	float CurrPitch = bVideoHatchOpened ? TargetPitch : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(CurrPitch, 0, 0));
}

ANewBomb::ANewBomb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	skeletalMesh->SetupAttachment(RootComponent);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	BoxCollision->SetCollisionProfileName("Trigger");

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ANewBomb::onOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ANewBomb::onOverlapEnd);
	activated = true;
	deactivated = false;
	timeElapsed = false;

}

void ANewBomb::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANewBomb, bVideoHatchOpened);
}