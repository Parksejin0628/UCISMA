// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatUnit/Enemy/DestructableObstacleBase.h"
#include "BeatUnit/Enemy/EnemyStatComp.h"
#include "Components/StaticMeshComponent.h"
#include "BeatUnit/DestructedActor.h"

ADestructableObstacleBase::ADestructableObstacleBase()
{
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle Mesh"));
	ObstacleMesh->SetupAttachment(RootComponent);
	ObstacleMesh->SetCollisionProfileName(TEXT("ObstacleCollider"));

	ConstructorHelpers::FObjectFinder<UMaterialInstance> OverlayMaterialAsset(TEXT("/Game/FX/M_Outline/MI_Overlay"));
	ObstacleMesh->SetOverlayMaterial(OverlayMaterialAsset.Object);
}

void ADestructableObstacleBase::HitReaction(float Damage, EJudgementResult Judgement)
{
	EnemyStatComp->DecreaseHealth(Damage);
	SpawnHitFx(Judgement);

	if (Judgement == EJudgementResult::DashPerfect || Judgement == EJudgementResult::AttackPerfect)
	{
		UpdatePlayerRecordOnPerfectHit();
	}

	if (EnemyStatComp->IsDead())
	{
		OnDie();
	}
}

void ADestructableObstacleBase::OnDie()
{
	LOG_PSJ(Display, TEXT("Destructable Obstacle Base is Died"));

	StageManager->AddScore(EScoreType::KillEnemy);
	DestructedActor = SpawnDestructedActor();
	AddImpulseToDestructedActor(DestructedActor);

	DeactiveUnit();
}

ADestructedActor* ADestructableObstacleBase::SpawnDestructedActor()
{
	return GetWorld()->SpawnActor<ADestructedActor>(DestructedClass, GetActorLocation(), GetActorRotation());
}

void ADestructableObstacleBase::AddImpulseToDestructedActor(ADestructedActor* Target)
{
	FVector ThisLocation = GetActorLocation();
	FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

	FVector DestroyDir = (ThisLocation - PlayerLocation).GetSafeNormal();
	FVector DestroyImpulse = { DestroyDir.X * DestroyPower, DestroyDir.Y * DestroyPower, -DestroyPower };

	Target->AddImpulse(DestroyImpulse);
}

