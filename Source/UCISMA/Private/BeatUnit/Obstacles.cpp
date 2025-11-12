// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatUnit/Obstacles.h"
#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "UObject/ConstructorHelpers.h"

AObstacles::AObstacles()
{
    PrimaryActorTick.bCanEverTick = true;

    objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
    RootComponent = objectMesh;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxCollision->SetupAttachment(RootComponent);

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AObstacles::OnOverlapBegin);
    BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AObstacles::BeginPlay()
{
    Super::BeginPlay();

    if (!bCanDealDamage || !auraMaterial) return;
    // 🔹 대미지 이펙트 활성화 여부 설정
    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(auraMaterial, this);
    objectMesh->SetOverlayMaterial(DynamicMaterial);
}

void AObstacles::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AObstacles::KnockBack(AActor* player)
{
    if (player)
    {
        // 방향 계산
        FVector PushDirection = (player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        FVector PushForce = PushDirection * 1000.0f; // 1000.0f는 강도 값
        PushForce.Z = 0;

        APlayerCharacter* Player = Cast<APlayerCharacter>(player);

        // 밀어내기
        Player->LaunchCharacter(PushForce, true, true);
        Player->Take_HP(-damageAmount, this);
    }
}

void AObstacles::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    if (OtherActor->ActorHasTag(FName("PurificationTarget"))) return;

    // 충돌한 오브젝트가 플레이어인지 확인
    if (Cast<APlayerCharacter>(OtherActor) && bCanDealDamage)
    {
        KnockBack(OtherActor);
        return;  // 플레이어와 충돌 시 아무 행동도 하지 않음
    }
}

