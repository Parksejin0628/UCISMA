// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatUnit/BeatUnitActor_Obstacles_Spline.h"
#include "LevelDesign/Spline/SplineController.h"

void ABeatUnitActor_Obstacles_Spline::SetOnSpline(ASplineController* Controller, int32 ArrayIndex)
{
	if (HasOwnerSpline(Controller)) {
		OwnerSpline->DeleteObstacle(OwnerSplineArrayIndex);
	}
	OwnerSpline = Controller;
	OwnerSplineArrayIndex = ArrayIndex;
	MoveType = EMoveType::Spline;
    collisionResponse = ECollisionResponseType::Ignore;
}

void ABeatUnitActor_Obstacles_Spline::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (MoveType != EMoveType::Spline || !OwnerSpline) return;

    FVector NewLocation;
    bool bReachedEnd = false;

    // 각 액터의 bIsReversing 개별 전달
    if (OwnerSpline->GetSplineLocation(Time, bIsReversing, NewLocation, bReachedEnd))
    {
        SetActorLocation(NewLocation);
    }

    // 끝 도달 처리
    if (bReachedEnd)
    {
        switch (EndReactType)
        {
        case ESplineEndReactType::Loop:
            Time = 0.f;
            break;

        case ESplineEndReactType::Reverse:
            Time = 0.f;
            bIsReversing = !bIsReversing;
            // 방향 전환 후 다음 프레임부터 자연스럽게 이동
            //Time = FMath::Clamp(Time - DeltaTime, 0.f, OwnerSpline->Time);
            break;

        case ESplineEndReactType::Disappear:
            DeactiveUnit();
            return;

        case ESplineEndReactType::Stop:
        default:
            return; // 그냥 멈춤
        }
    }

    // 개별 액터의 Time 갱신
    Time += DeltaTime;
}

bool ABeatUnitActor_Obstacles_Spline::HasOwnerSpline(ASplineController* SpineController)
{
	return OwnerSpline && OwnerSpline != SpineController;
}

void ABeatUnitActor_Obstacles_Spline::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // 여기에 액터가 삭제될 때 처리할 코드 작성
    UE_LOG(LogTemp, Warning, TEXT("EndPlay called for %s"), *GetName());

    if (HasOwnerSpline(OwnerSpline)) {
        OwnerSpline->DeleteObstacle(OwnerSplineArrayIndex);
    }

    Super::EndPlay(EndPlayReason);
}

void ABeatUnitActor_Obstacles_Spline::ActiveUnit()
{
	Super::ActiveUnit();
	Time = 0;
}

