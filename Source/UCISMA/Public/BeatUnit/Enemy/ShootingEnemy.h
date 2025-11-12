// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCISMA/UCISMA.h"
#include "System/CommonTypes.h"
#include "BeatUnit/Enemy/EnemyBase.h"
#include "ShootingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UCISMA_API AShootingEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	//유닛 활성화 시 호출되는 함수
	virtual void ActiveUnit() override;
	//매 QuaterBeat마다 호출되는 함수
	virtual void BeatUpdate(int QuaterIndex) override;
	//주어진 ProjectileInformation을 바탕으로 투사체 발사
	void ShootProjectile(const FProjectileInformation& ProjectileInformation);

protected:
	class IProjectileInterface* GetProjectile(const FProjectileInformation& ProjectileInformation);
private:
	//생성자
	AShootingEnemy();
	//슈팅과 관련된 초기 설정을 하는 함수
	void InitShootingSetting();
	//전달받은 Patterns를 바탕으로 패턴의 설정에 따라 사격 방식을 제어하는 함수
	void HandleShootingSetting(TArray<FShootingPatternSetting*>& Patterns, int QuaterBeat);
	//정해진 타이밍에 패턴 정보를 리턴하는 함수, 패턴 사이클을 제어한다.
	TArray<FShootingPatternSetting*> HandlePatternCycle();
	//패턴에 설정된 일반 사격을 하는 함수
	void ShootNormalSetting(FShootingPatternSetting& Pattern, int QuaterBeat);
	//패턴에 설정된 디테일 사격을 하는 함수
	void ShootDetailSetting(FShootingPatternSetting& Pattern);
	
	//모든 패턴의 Default값이 되는 Projectile 값, 투사체로 발사되는 객체의 클래스
	UPROPERTY(EditAnywhere, Category = "Design Settings|Projectile")
	TSubclassOf<class ALinearProjectile> DefaultProjectile;
	//모든 패턴의 Default 값이 되는 Speed 값, 비트당 투사체의 이동거리
	UPROPERTY(EditAnywhere, Category = "Design Settings|Projectile")
	float DefaultSpeed;
	//모든 패턴의 Default 값이 되는 Range 값, 투사체가 시작 지점으로 부터 최대로 떨어질 수 있는 거리
	UPROPERTY(EditAnywhere, Category = "Design Settings|Projectile")
	float DefaultRange;
	//모든 패턴의 Default 값이 되는 IsUseCustomStandardOfAngle 값, 플레이어를 바라보는 방향을 Angle의 기준으로 할 것인지(false일 때), 별도로 설정된 방향을 Angle의 기준으로 할지에 대한 여부(true 일 때)
	UPROPERTY(EditAnywhere, Category = "Design Settings|Projectile")
	bool bDefaultIsUseCustomStandardOfAngle;
	//모든 패턴의 Default 값이 되는 CustomStandardOfAngle 값, 별도의 방향을 기준으로 Angle값을 정할 경우 그 기준이 되는 값
	UPROPERTY(EditAnywhere, Category = "Design Settings|Projectile", meta = (EditCondition = "bDefaultIsUseCustomStandardOfAngle", EditConditionHides))
	float DefaultCustomStandardOfAngle;
	//모든 패턴의 Default 값이 되는 Angle 값, 기준을 바탕으로 Angle만큼 각도가 꺾여서 투사체가 발사된다.
	UPROPERTY(EditAnywhere, Category = "Design Settings|Projectile")
	float DefaultAngle;
	//사격 패턴들
	UPROPERTY(EditAnywhere, Category = "Design Settings|Projectile")
	TArray<FShootingPatternSetting> ShootingPatterns;
	
	//현재 진행중인 패턴의 Index
	int PatternIndex;


	
};
