// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatUnit/PuddleOfWater.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayerCharacter.h"
#include "NiagaraSystem.h"

// Sets default values
APuddleOfWater::APuddleOfWater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.2f;

	PuddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Puddle Mesh"));
	RootComponent = PuddleMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

	PuddleMesh->SetRenderCustomDepth(true);

	PuddleMesh->SetCustomDepthStencilValue(10);

	WaveCountPerSecond = 10;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> WaveFxAsset(TEXT("/Game/FX/WaterWave/NS_WaterWave.NS_WaterWave"));
	if (WaveFxAsset.Succeeded())
	{
		WaveFx = WaveFxAsset.Object;
	}
	else
	{
		LOG_DEBUG(Error, TEXT("Wave Fx Can't Load"));
	}
}

// Called when the game starts or when spawned
void APuddleOfWater::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.TickInterval = 1.0f / FMath::Max(1.0f, WaveCountPerSecond);
	LOG_PSJ(Display, TEXT("Tick Interval : %f"), 1.0f / FMath::Max(1.0f, WaveCountPerSecond))

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APuddleOfWater::OnComponentBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &APuddleOfWater::OnComponentEndOverlap);
}

// Called every frame
void APuddleOfWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	LOG_PSJ_SCREEN_WITH_ID(37, 1.0f, TEXT("ActorsOnPuddle Count : %d"), ActorsOnPuddle.Num());

	for (AActor* Target : ActorsOnPuddle)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), WaveFx, Target->GetActorLocation(), GetActorRotation());
	}

	
}

void APuddleOfWater::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		ActorsOnPuddle.AddUnique(OtherActor);
	}
}

void APuddleOfWater::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		ActorsOnPuddle.Remove(OtherActor);
	}
	
}


