// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCISMA/UCISMA.h"
#include "BeatUnit/Obstacles.h"
#include "BeatUnitActor_Obstacles.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMoveInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BeatIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 QuarterIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MoveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector MoveDirection;
};

UCLASS()
class UCISMA_API ABeatUnitActor_Obstacles : public AObstacles
{
	GENERATED_BODY()
public:
    ABeatUnitActor_Obstacles();

protected:
    virtual void BeginPlay() override;
    virtual void BeatUpdate(int QuaterIndex) override;

public:
    virtual void Serialize(FArchive& Ar) override;
    virtual void Tick(float DeltaTime) override;
    int GetEndBeatIndex() { return EndBeatIndex; };
    void SetEndBeatIndex(int32 value) { this->EndBeatIndex = value; }

    // ======================= [ 디테일 창에서 설정 가능하도록 UPROPERTY 추가 ] =======================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings")
    bool bCanMove = false;

    // 🔹 이동 속도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings", meta = (EditCondition = "MoveType == EMoveType::Self"))
    float moveSpeed = 200.0f;

    // 🔹 이동 방향
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings", meta = (EditCondition = "MoveType == EMoveType::Self"))
    FVector moveDirection = FVector(1.0f, 0.0f, 0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings|MoveArray", meta = (EditCondition = "MoveType == EMoveType::Self", EditConditionHides))
    TArray<FMoveInfo> MoveArray;

private:
    bool bOnSpine = false;
    FVector CurrentVelocity;

    virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
