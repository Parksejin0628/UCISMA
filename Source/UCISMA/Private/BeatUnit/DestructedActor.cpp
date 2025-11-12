// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatUnit/DestructedActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
ADestructedActor::ADestructedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Geometry Collection"));
	RootComponent = GeometryCollection;
	GeometryCollection->SetDamageThreshold({ 0.1f });
	GeometryCollection->SetEnableGravity(true);
	GeometryCollection->SetCollisionProfileName(TEXT("DestructedActor"));
}

// Called when the game starts or when spawned
void ADestructedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructedActor::AddImpulse(FVector Impulse)
{
	GeometryCollection->AddImpulse(Impulse, NAME_None, true);
}

