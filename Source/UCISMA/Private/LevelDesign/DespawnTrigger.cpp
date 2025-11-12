// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/DespawnTrigger.h"
#include "Components/BoxComponent.h"
#include "BeatUnit/Obstacles.h"

// Sets default values
ADespawnTrigger::ADespawnTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DespawnTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DespawnTriggerBox"));
	RootComponent = DespawnTriggerBox;

	if (!DespawnTriggerBox)
	{
		UE_LOG(LogTemp, Error, TEXT("[Error] DespawnTriggerBox is nullptr!"));
	}
}

// Called when the game starts or when spawned
void ADespawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	DespawnTriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADespawnTrigger::OnDespawnObstacle);
}

void ADespawnTrigger::OnDespawnObstacle(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AObstacles* Obstacle = Cast<AObstacles>(OtherActor);
	if (!Obstacle) return;

	//LOG_KHJ_SCREEN(3.0f, TEXT("%s"), *Obstacle->GetName());
	Obstacle->DeactiveUnit();
}