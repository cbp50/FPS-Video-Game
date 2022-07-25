// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Boy.h"
#include "BrokenBoyGameModeBase.h"
#include "DefusionGameStateBase.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	skeletalMesh->SetupAttachment(RootComponent);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	BoxCollision->SetCollisionProfileName("Trigger");

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABomb::onOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABomb::onOverlapEnd);
	activated = true;
	deactivated = false;
	timeElapsed = false;

	
	

}

void ABomb::onOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
			
		}
	}
	else if (OtherActor->ActorHasTag("Defender")) {
		Boy = Cast<ABoy>(OtherActor);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Can Defuse");
		Boy->defuse();
	}
	
}

void ABomb::onOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Also we need to check if Boy has the bomb
	

	

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// look at this
void ABomb::defuse(bool &active) {
	
	active = false;
}

void ABomb::activate(bool &active) {
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Activated");
	active = true;
	//button to change this to true
}





