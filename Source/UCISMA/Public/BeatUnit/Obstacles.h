// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCISMA/UCISMA.h"
#include "BeatUnitActor.h"
#include "Components/BoxComponent.h"
#include "Obstacles.generated.h"

UENUM(BlueprintType)
enum class ECollisionResponseType : uint8
{
	Stop UMETA(DisplayName = "멈추기"),
	Ignore UMETA(DisplayName = "무시하기"),
	Reverse UMETA(DisplayName = "반대 방향으로 움직이기"),
	Destroy UMETA(DisplayName = "사라지기")
};

UENUM(BlueprintType)
enum class EMoveType : uint8
{
	None UMETA(DisplayName = "움직이지 않음"),
	Self UMETA(DisplayName = "혼자 움직임"),
	Spline UMETA(DisplayName = "스플라인으로 움직임")
};

UCLASS()
class UCISMA_API AObstacles : public ABeatUnitActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacles();


protected:
	// 🔹 오브젝트 이동 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings")
	EMoveType MoveType = EMoveType::None;

	// 🔹 오브젝트가 대미지를 주는 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings")
	bool bCanDealDamage = false;

	// 🔹 대미지 값 (bCanDealDamage가 true일 때 적용됨)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings", meta = (EditCondition = "bCanDealDamage"))
	float damageAmount = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings", meta = (EditCondition = "bCanDealDamage"))
	UMaterialInstance* auraMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* objectMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void KnockBack(AActor* player);

	// 🔹 충돌 시 행동 (멈추기, 무시하기, 반대 방향, 삭제)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design Settings")
	ECollisionResponseType collisionResponse = ECollisionResponseType::Stop;

	AActor* PreviouslyBumpedActor;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
