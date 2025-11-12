// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCISMA/UCISMA.h"
#include "GameFramework/Actor.h"
#include "DestructedActor.generated.h"

UCLASS()
class UCISMA_API ADestructedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructedActor();
	UFUNCTION(BlueprintCallable)
	void AddImpulse(FVector Impulse);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design Settings")
	class UGeometryCollectionComponent* GeometryCollection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


};
