// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCISMA/UCISMA.h"
#include "Components/ActorComponent.h"
#include "EnemyStatComp.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UCISMA_API UEnemyStatComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyStatComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float CurrentHealth;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//void SetNewLevel(int32 Level);
	int32 GetMaxHealth() { return MaxHealth; }
	int32 GetCurrentHealth() { return CurrentHealth; }

	void InitHealth(int32 MaxHealth);
	void IncreaseHealth(float value);
	bool DecreaseHealth(float value);

	float GetHealthPercent() const; // Ã¼·Â ¹éºÐÀ² ¹ÝÈ¯

	bool IsDead() const;
};