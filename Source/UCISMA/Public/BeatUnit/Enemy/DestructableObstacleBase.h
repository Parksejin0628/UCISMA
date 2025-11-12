// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCISMA/UCISMA.h"
#include "BeatUnit/Enemy/EnemyBase.h"
#include "DestructableObstacleBase.generated.h"

/**
 * 
 */
UCLASS()
class UCISMA_API ADestructableObstacleBase : public AEnemyBase
{
	GENERATED_BODY()
public:
	class ADestructedActor* SpawnDestructedActor();

	void AddImpulseToDestructedActor(class ADestructedActor* Target);

protected:
	virtual void HitReaction(float Damage, EJudgementResult Judgement) override;
	virtual void OnDie();
private:
	ADestructableObstacleBase();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(EditAnywhere, Category = "Design Settings")
	TSubclassOf<class ADestructedActor> DestructedClass;

	UPROPERTY()
	class ADestructedActor* DestructedActor;

	UPROPERTY(EditAnywhere, Category = "Design Settings")
	float DestroyPower;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* OverlayMaterial;
};
