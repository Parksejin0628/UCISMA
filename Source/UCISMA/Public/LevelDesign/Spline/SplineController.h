// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineController.generated.h"

UCLASS()
class UCISMA_API ASplineController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineController();
	
	void DeleteObstacle(int32 MoveActorsIndex);
 
	bool GetSplineLocation(float ObjTime, bool bReverse, FVector& OutLocation, bool& bOutReachedEnd) const;
	
	FORCEINLINE bool GetRevese() { return bIsReversing; }
	FORCEINLINE void SetRevesing(bool re) { this->bIsReversing = re; }

	float Time;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USplineComponent* Spline;

	//해당 스플라인에서 움직일 액터들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings")
	TArray<class ABeatUnitActor_Obstacles_Spline*> MoveActors;
private:

	void InitSpineValue();
	//액터가 몇 Beat만큼 움직이는가
	UPROPERTY(EditAnywhere, Category = "Design Settings")
	int DuringBeat;

	//액터가 몇 QuterBeat만큼 움직이는가
	UPROPERTY(EditAnywhere, Category = "Design Settings")
	int DuringQuterBeat;

	bool bIsReversing;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
