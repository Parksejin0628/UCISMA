// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeatUnit/Obstacles.h"
#include "LevelDesign/Spline/MovableOnSpline.h"
#include "BeatUnitActor_Obstacles_Spline.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESplineEndReactType : uint8
{
	Stop UMETA(DisplayName = "Stop"),
	Loop UMETA(DisplayName = "Loop"),
	Reverse UMETA(DisplayName = "Reverse"),
	Disappear UMETA(DisplayName = "Disappear")
};

UCLASS()
class UCISMA_API ABeatUnitActor_Obstacles_Spline : public AObstacles, public IMovableOnSpline
{
	GENERATED_BODY()
public:
	virtual void SetOnSpline(class ASplineController* SpineController, int32 ArrayIndex) override;
	
	virtual void Tick(float DeltaTime) override;

	bool HasOwnerSpline(class ASplineController* SpineController);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASplineController* OwnerSpline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 OwnerSplineArrayIndex;

	//물체가 끝에 도달하면 취할 행동
	UPROPERTY(EditAnywhere, Category = "Design Settings")
	ESplineEndReactType EndReactType;
protected:
	virtual void EndPlay(const EEndPlayReason::Type) override;

private:
	virtual void ActiveUnit() override;

	float Time = 0;
	bool bIsReversing = false;
};
