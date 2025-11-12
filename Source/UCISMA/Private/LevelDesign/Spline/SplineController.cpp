// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/Spline/SplineController.h"
#include "Components/SplineComponent.h"
#include "BeatUnit/BeatUnitActor_Obstacles_Spline.h"
#include "Manager/StageManager.h"

// Sets default values
ASplineController::ASplineController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;
	Time = 1;
	bIsReversing = false;
}

bool ASplineController::GetSplineLocation(float ObjTime, bool bReverse, FVector& OutLocation, bool& bOutReachedEnd) const
{
	bOutReachedEnd = false;
	if (Time == 0.f) return false;

	float Alpha = bReverse ? 1.f - (ObjTime / Time) : ObjTime / Time;
	Alpha = FMath::Clamp(Alpha, 0.f, 1.f);

	const float SplineDistance = Spline->GetSplineLength();
	float CurDistance = FMath::Lerp(0.f, SplineDistance, Alpha);
	OutLocation = Spline->GetLocationAtDistanceAlongSpline(CurDistance, ESplineCoordinateSpace::World);

	if ((!bReverse && Alpha >= 1.f) || (bReverse && Alpha <= 0.f))
	{
		bOutReachedEnd = true;
	}

	return true;
}


// Called when the game starts or when spawned
void ASplineController::BeginPlay()
{
	Super::BeginPlay();

	InitSpineValue();

	for (int32 i = MoveActors.Num() - 1; i >= 0; --i)
	{
		ABeatUnitActor_Obstacles_Spline* obstacle = MoveActors[i];
		if (obstacle->Implements<UMovableOnSpline>())
		{
			if (obstacle->HasOwnerSpline(this))
			{
				UE_LOG(LogTemp, Error, TEXT("new: %s"),
					obstacle ? *obstacle->GetName() : TEXT("nullptr"));
				//다른 스플라인에 액터가 존재하면 삭제
				MoveActors.RemoveAt(i);
			}
		}
	}
}

#if WITH_EDITOR
FString ChangeTypeToString(EPropertyChangeType::Type ChangeType)
{
	switch (ChangeType)
	{
	case EPropertyChangeType::Unspecified:   return TEXT("Unspecified");
	case EPropertyChangeType::ValueSet:      return TEXT("ValueSet");
	case EPropertyChangeType::ArrayAdd:      return TEXT("ArrayAdd");
	case EPropertyChangeType::ArrayRemove:   return TEXT("ArrayRemove");
	case EPropertyChangeType::ArrayClear:    return TEXT("ArrayClear");
	case EPropertyChangeType::Duplicate:     return TEXT("Duplicate");
	case EPropertyChangeType::Interactive:   return TEXT("Interactive");
	case EPropertyChangeType::Redirected:    return TEXT("Redirected");
	default:                                 return TEXT("Unknown");
	}
}

void ASplineController::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property &&
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(ASplineController, MoveActors))
	{
		UE_LOG(LogTemp, Error, TEXT("ChangeType = %s"),
			*ChangeTypeToString(PropertyChangedEvent.ChangeType));
		if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ValueSet)
		{
			int32 ChangedIndex = PropertyChangedEvent.GetArrayIndex(PropertyChangedEvent.Property->GetName());

			if (MoveActors.IsValidIndex(ChangedIndex))
			{
				ABeatUnitActor_Obstacles_Spline* NewObstacle = MoveActors[ChangedIndex];
				NewObstacle->SetOnSpline(this, ChangedIndex);

				UE_LOG(LogTemp, Warning, TEXT("new: %s"),
					NewObstacle ? *NewObstacle->GetName() : TEXT("nullptr"));
			}
		}
	}
}
#endif

void ASplineController::DeleteObstacle(int32 MoveActorsIndex)
{
	if (MoveActors.IsValidIndex(MoveActorsIndex)) {
		MoveActors.RemoveAt(MoveActorsIndex);
	}
}


void ASplineController::InitSpineValue()
{
	AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
	Time = (DuringBeat + DuringQuterBeat / StageManager->GetBeatUpdateCallRate()) * StageManager->GetSecondPerBeat();
	//LOG_KHJ(Display, TEXT("%f"), Time);
}

// Called every frame
void ASplineController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

