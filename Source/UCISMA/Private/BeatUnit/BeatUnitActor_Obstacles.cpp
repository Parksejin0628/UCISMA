// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatUnit/BeatUnitActor_Obstacles.h"
#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BeatUnit/ActorComponent/UBeatRotatorComponent.h"
#include "Kismet/GameplayStatics.h"

ABeatUnitActor_Obstacles::ABeatUnitActor_Obstacles()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ABeatUnitActor_Obstacles::BeginPlay()
{
    Super::BeginPlay();

    // 🔹 이동 속도 설정
    if (MoveType == EMoveType::Self)
    {
        CurrentVelocity = moveDirection.GetSafeNormal() * moveSpeed;
    }
}

void ABeatUnitActor_Obstacles::BeatUpdate(int QuaterIndex)
{
    Super::BeatUpdate(QuaterIndex);

    for (auto& Move : MoveArray)
    {
        if (Move.BeatIndex == CurrentBeatIndex &&
            Move.QuarterIndex == QuaterIndex)
        {
            CurrentVelocity = Move.MoveDirection.GetSafeNormal() * Move.MoveSpeed;
        }
    }
}

void ABeatUnitActor_Obstacles::Serialize(FArchive& Ar)
{
    Super::Serialize(Ar);

    if (Ar.IsLoading())
    {
        // bool 값이 설정되어 있으면 MoveType으로 매핑
        if (bCanMove)
        {
            if (MoveType == EMoveType::None) // 아직 값이 기본값일 때만 변환
            {
                MoveType = EMoveType::Self;
            }
        }
        else
        {
            if (MoveType == EMoveType::None)
            {
                MoveType = EMoveType::None;
            }
        }
    }
}

void ABeatUnitActor_Obstacles::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!GetIsLiving()) return;

    if (MoveType == EMoveType::Self)
    {
        FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
        SetActorLocation(NewLocation);  
    }
}

void ABeatUnitActor_Obstacles::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    if (OtherActor->ActorHasTag(FName("PurificationTarget"))) return;

    // 충돌한 오브젝트가 플레이어인지 확인
    if (Cast<APlayerCharacter>(OtherActor) && bCanDealDamage)
    {
        KnockBack(OtherActor);
        return;  // 플레이어와 충돌 시 아무 행동도 하지 않음
    }

    if (OtherActor == PreviouslyBumpedActor || OtherActor->ActorHasTag(FName("Tag_Camera"))) return;

    switch (collisionResponse)
    {
    case ECollisionResponseType::Stop:
        MoveType = EMoveType::None;
        CurrentVelocity = FVector::ZeroVector;
        //LOG_KHJ_SCREEN(3.0f, TEXT("오브젝트 정지!"));
        break;

    case ECollisionResponseType::Ignore:
        // LOG_KHJ_SCREEN(3.0f, TEXT("충돌 무시하고 이동 계속!"));
        break;

    case ECollisionResponseType::Reverse:
        CurrentVelocity *= -1.0f;
        //LOG_KHJ_SCREEN(3.0f, TEXT("반대 방향으로 이동!"));
        break;

    case ECollisionResponseType::Destroy:
        //LOG_KHJ_SCREEN(3.0f, TEXT("오브젝트 삭제!"));
        Destroy();
        break;
    }

    PreviouslyBumpedActor = OtherActor;
}