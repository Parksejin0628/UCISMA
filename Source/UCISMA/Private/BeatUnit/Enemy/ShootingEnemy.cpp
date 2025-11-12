// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatUnit/Enemy/ShootingEnemy.h"
#include "Projectile/LinearProjectile.h"
#include "PlayerCharacter.h"
#include "Projectile/ProjectileInterface.h"

AShootingEnemy::AShootingEnemy()
{
	bCallBeatUpdateOnSpawn = true;
}

void AShootingEnemy::ActiveUnit()
{
	Super::ActiveUnit();

	InitShootingSetting();
	
}

void AShootingEnemy::InitShootingSetting()
{
	//일반 사격의 BeatLength가 0인 경우 무한하게 사격하는 것으로 설정
	for (FShootingPatternSetting& Pattern : ShootingPatterns)
	{
		if (Pattern.ProjectileNormalSetting.ShootingBeatLength == 0)
		{
			Pattern.ProjectileNormalSetting.ShootingBeatLength = std::numeric_limits<int>::max();
		}
	}
	PatternIndex = 0;
}

void AShootingEnemy::BeatUpdate(int QuaterIndex)
{
	if (!GetIsLiving())
	{
		return;
	}
	//HandlePatternCycle에서 현재 패턴들을 받아온 후 HandleShootingSetting으로 전달하여 사격 실행
	TArray<FShootingPatternSetting*> Patterns = HandlePatternCycle();
	HandleShootingSetting(Patterns, QuaterIndex);
}

void AShootingEnemy::HandleShootingSetting(TArray<FShootingPatternSetting*>& Patterns, int QuaterBeat)
{
	for (FShootingPatternSetting* Pattern : Patterns)
	{
		//현재 패턴이 일반 사격인 경우
		if (Pattern->bUseDetailSetting)
		{
			Pattern->ProjectileDetailSetting.UpdateSettingCoolTime(StageManager);
			if (!Pattern->ProjectileDetailSetting.IsCoolTime())
			{
				ShootDetailSetting(*Pattern);
			}
		}
		//현재 패턴이 디테일 사격인 경우
		else if(Pattern->bUseNormalSetting)
		{
			if (QuaterBeat == 0)
			{
				Pattern->ProjectileNormalSetting.UpdateSettingCoolTime();
			}
			if (!Pattern->ProjectileNormalSetting.IsCoolTime())
			{
				ShootNormalSetting(*Pattern, QuaterBeat);
			}
		}
	}
}

TArray<FShootingPatternSetting*> AShootingEnemy::HandlePatternCycle()
{
	TArray<FShootingPatternSetting*> Patterns;
	//PatternIndex가 ShootingPatterns의 배열 범위를 벗어나는 경우 예외처리
	if (ShootingPatterns.Num() <= PatternIndex)
	{
		LOG_DEBUG(Error, TEXT("Shooting Enemy's PatternIndex is Wrong"));
		return Patterns;
	}
	//현재 패턴을 임시로 리턴 값에 추가
	Patterns.Add(&ShootingPatterns[PatternIndex]);
	int PatternLength = Patterns[0]->PatternLength_Beat * StageManager->GetBeatUpdateCallRate() + Patterns[0]->PatternLegnth_QuaterBeat;
	Patterns[0]->ProgressBeat++;
	
	//만약 패턴이 종료되는 시점인 경우 다음 패턴으로 넘어감
	if (Patterns[0]->ProgressBeat >= PatternLength)
	{
		PatternIndex = (PatternIndex + 1) % ShootingPatterns.Num();
		while (ShootingPatterns[PatternIndex].bExecuteConcurrentWithPrevious)
		{
			PatternIndex = (PatternIndex + 1) % ShootingPatterns.Num();
		}
		Patterns.Empty();
		Patterns.Add(&ShootingPatterns[PatternIndex]);
		Patterns[0]->ProgressBeat = 0;
	}

	//현재 패턴 후에 있는 패턴들 중 동시에 발동되게 한 패턴이 있을 경우 리턴하는 패턴에 추가
	for (int i = PatternIndex + 1; i < ShootingPatterns.Num(); i++)
	{
		if (!ShootingPatterns[i].bExecuteConcurrentWithPrevious)
		{
			break;
		}
		Patterns.Add(&ShootingPatterns[i]);
	}

	return Patterns;
}

void AShootingEnemy::ShootNormalSetting(FShootingPatternSetting& Pattern, int QuaterBeat)
{
	//비트당 슈팅 횟수 조절
	if (QuaterBeat == 0 && Pattern.ProjectileNormalSetting.ShootingCountPerBeat == EShootingCountPerBeat::Zero)
	{
		return;
	}
	if (QuaterBeat == 1 && Pattern.ProjectileNormalSetting.ShootingCountPerBeat != EShootingCountPerBeat::Max)
	{
		return;
	}
	if (QuaterBeat == 2 && !(Pattern.ProjectileNormalSetting.ShootingCountPerBeat == EShootingCountPerBeat::Two || Pattern.ProjectileNormalSetting.ShootingCountPerBeat == EShootingCountPerBeat::Max))
	{
		return;
	}
	if (QuaterBeat == 3 && Pattern.ProjectileNormalSetting.ShootingCountPerBeat != EShootingCountPerBeat::Max)
	{
		return;
	}

	//투사체 정보 설정
	FProjectileInformation TempProjectileInformation;
	TempProjectileInformation.StartPosition = this->GetActorLocation() + FVector::ZAxisVector * -30;
	TempProjectileInformation.TargetClass = APlayerCharacter::StaticClass();
	//투사체 클래스 설정
	if (Pattern.ProjectileNormalSetting.bIsUseDetailProjectile && Pattern.ProjectileNormalSetting.ProjectileClass)
	{
		TempProjectileInformation.Projectile = Pattern.ProjectileNormalSetting.ProjectileClass;
	}
	else
	{
		TempProjectileInformation.Projectile = DefaultProjectile;
	}
	//투사체 속도 결정
	if (Pattern.ProjectileNormalSetting.bIsUseDetailSpeed && Pattern.ProjectileNormalSetting.ProjectileSpeed > 0)
	{
		TempProjectileInformation.ProjectileSpeed = Pattern.ProjectileNormalSetting.ProjectileSpeed;
	}
	else
	{
		TempProjectileInformation.ProjectileSpeed = DefaultSpeed;
	}
	//투사체 사거리 결정
	if (Pattern.ProjectileNormalSetting.bIsUseDetailRange && Pattern.ProjectileNormalSetting.ProjectileRange > 0)
	{
		TempProjectileInformation.ProjectileRange = Pattern.ProjectileNormalSetting.ProjectileRange;
	}
	else
	{
		TempProjectileInformation.ProjectileRange = DefaultRange;
	}
	//첫 번째 투사체의 각도 설정 (적 기준 가장 왼쪽 총알부터 발사하게 된다.)
	FRotator StandardOfAngle;
	
	if (Pattern.ProjectileNormalSetting.bIsUseDetailCustomStandardOfAngle)
	{
		if (Pattern.ProjectileNormalSetting.bIsUseCustomStandardOfAngle)
		{
			StandardOfAngle = FRotator(0, Pattern.ProjectileNormalSetting.CustomStandardOfAngle, 0);
		}
		else
		{
			StandardOfAngle = this->GetActorRotation();
		}
	}
	else
	{
		if (bDefaultIsUseCustomStandardOfAngle)
		{
			StandardOfAngle = FRotator(0, DefaultCustomStandardOfAngle, 0);
		}
		else
		{
			StandardOfAngle = this->GetActorRotation();
		}
	}
	FRotator FirstShootingAngle = StandardOfAngle + FRotator(0, Pattern.ProjectileNormalSetting.ProjectileAngleGap / 2 * (Pattern.ProjectileNormalSetting.ProjectileCountPerShoot - 1) * -1, 0);
	LOG_PSJ(Display, TEXT("First shooting angle : [%f, %f, %f]"), FirstShootingAngle.Pitch, FirstShootingAngle.Yaw, FirstShootingAngle.Roll);
	
	//AngleGap에 따라 각도를 다르게 설정 후 발사
	for (int ProjectileNum = 0; ProjectileNum < Pattern.ProjectileNormalSetting.ProjectileCountPerShoot; ProjectileNum++)
	{
		TempProjectileInformation.ProjectileAngle = FirstShootingAngle + FRotator(0, Pattern.ProjectileNormalSetting.ProjectileAngleGap * ProjectileNum, 0);
		ShootProjectile(TempProjectileInformation);
	}
}

void AShootingEnemy::ShootDetailSetting(FShootingPatternSetting& Pattern)
{
	for (FProjectileSetting& DetailSetting : Pattern.ProjectileDetailSetting.ProjectileSettings)
	{
		//디테일 사격의 진행비트와 해당 투사체의 시작 비트가 일치하는지 확인
		if (Pattern.ProjectileDetailSetting.ProgressQuaterBeat != DetailSetting.Delay_Beat * StageManager->GetBeatUpdateCallRate() + DetailSetting.Delay_QuaterBeat)
		{
			continue;
		}
		LOG_PSJ_SCREEN_WITH_ID(12, 3.0f, TEXT("ProgressQuaterBeat : %d"), Pattern.ProjectileDetailSetting.ProgressQuaterBeat);
		//투사체 정보 설정
		FProjectileInformation ShootingProjectileInformation;
		if (DetailSetting.bIsUseDetailProjectile && DetailSetting.Projectile)
		{
			ShootingProjectileInformation.Projectile = DetailSetting.Projectile;
		}
		else
		{
			ShootingProjectileInformation.Projectile = DefaultProjectile;
		}

		if (DetailSetting.bIsUseDetailSpeed && DetailSetting.Speed > 0)
		{
			ShootingProjectileInformation.ProjectileSpeed = DetailSetting.Speed;
		}
		else
		{
			ShootingProjectileInformation.ProjectileSpeed = DefaultSpeed;
		}

		if (DetailSetting.bIsUseDetailRange && DetailSetting.Range > 0)
		{
			ShootingProjectileInformation.ProjectileRange = DetailSetting.Range;
		}
		else
		{
			ShootingProjectileInformation.ProjectileRange = DefaultRange;
		}

		FRotator StandardOfAngle;
		if (DetailSetting.bIsUseDetailCustomStandardOfAngle)
		{
			if (DetailSetting.bIsUseCustomStandardOfAngle)
			{
				StandardOfAngle = FRotator(0, DetailSetting.CustomStandardOfAngle, 0);
			}
			else
			{
				StandardOfAngle = this->GetActorRotation();
			}
		}
		else
		{
			if (bDefaultIsUseCustomStandardOfAngle)
			{
				StandardOfAngle = FRotator(0, DefaultCustomStandardOfAngle, 0);
			}
			else
			{
				StandardOfAngle = this->GetActorRotation();
			}
		}

		if (DetailSetting.bIsUseDetailAngle)
		{
			ShootingProjectileInformation.ProjectileAngle = StandardOfAngle + FRotator(0, DetailSetting.Angle, 0);
		}
		else
		{
			ShootingProjectileInformation.ProjectileAngle = StandardOfAngle + FRotator(0, DefaultAngle, 0);
		}
		
		ShootingProjectileInformation.StartPosition = this->GetActorLocation() + FVector::ZAxisVector * -30;
		ShootingProjectileInformation.TargetClass = APlayerCharacter::StaticClass();

		//설정을 마친 후 발사
		ShootProjectile(ShootingProjectileInformation);
	}
}

void AShootingEnemy::ShootProjectile(const FProjectileInformation& ProjectileInformation)
{
	//전달받은 ProjectileInformation을 바탕으로 투사체 생성
	IProjectileInterface* Projectile = GetProjectile(ProjectileInformation);
	if (!Projectile)
	{
		LOG_DEBUG(Display, TEXT("Shoot Enemy can't get projectile (Maybe destroyed as soon as created)"));
		return;
	}

	//생성한 투사체의 Shoot함수를 호출하여 투사체 발사
	Projectile->Shoot(ProjectileInformation);
}

IProjectileInterface* AShootingEnemy::GetProjectile(const FProjectileInformation& ProjectileInformation)
{
	IProjectileInterface* Projectile = GetWorld()->SpawnActor<ALinearProjectile>(ProjectileInformation.Projectile, GetActorLocation(), GetActorRotation());

	return Projectile;
}

