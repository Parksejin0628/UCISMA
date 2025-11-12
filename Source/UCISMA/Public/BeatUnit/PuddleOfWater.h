// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCISMA/UCISMA.h"
#include "GameFramework/Actor.h"
#include "PuddleOfWater.generated.h"

UCLASS()
class UCISMA_API APuddleOfWater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuddleOfWater();
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditAnywhere)
	int WaveCountPerSecond;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* WaveFx;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	TArray<AActor*> ActorsOnPuddle;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PuddleMesh;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereCollision;

};
