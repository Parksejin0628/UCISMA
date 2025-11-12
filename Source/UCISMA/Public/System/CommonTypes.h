// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCISMA/UCISMA.h"
#include "CommonTypes.generated.h"

//튜토리얼 단계 나눠놓음
UENUM(BlueprintType)
enum class ETutorialStep : uint8
{
	Step0 = 0 UMETA(DisplayName = "0~7 BeatIndex"),
	Step1 = 1 UMETA(DisplayName = "8~15 BeatIndex"),
	Step2 = 2 UMETA(DisplayName = "16~23 BeatIndex"),
	Step3 = 3 UMETA(DisplayName = "24~31 BeatIndex"),
	Step4 = 4 UMETA(DisplayName = "32~39 BeatIndex"),
	Step5 = 5 UMETA(DisplayName = "40~47  BeatIndex"),
	Step6 = 6 UMETA(DisplayName = "48~55  BeatIndex"),
	Step7 = 7 UMETA(DisplayName = "56~63  BeatIndex"),
	Step8 = 8 UMETA(DisplayName = "64~71  BeatIndex"),
	Step9 = 9 UMETA(DisplayName = "72~79 BeatIndex"),
	Step10 = 10 UMETA(DisplayName = "80~87 BeatIndex"),
	StepFinal = 11 UMETA(DisplayName = "88~96 BeatIndex")
};

UENUM(BlueprintType)
enum class EUIType : uint8
{
	SongProcessBar = 0 UMETA(DisplayName = "SongProcessBar"),
	HealthBar = 1 UMETA(DisplayName = "HealthBar"),
	BeatBar = 2 UMETA(DisplayName = "BeatBar"),
	BeatNode = 3 UMETA(DisplayName = "BeatBarNode"),
	Score = 4 UMETA(DisplayName = "Score"),
	Combo = 5 UMETA(DisplayName = "Combo"),
	State = 6 UMETA(DisplayName = "State")
};

//효과음 종류
UENUM(BlueprintType)
enum class ESfx : uint8
{
	AttackHitNormal UMETA(DisplayName = "Attack Hit Normal"),
	AttackHitGood UMETA(DisplayName = "Attack Hit Good"),
	AttackHitGreat UMETA(DisplayName = "Attack Hit Great"),
	AttackHitPerfect UMETA(DisplayName = "Attack Hit Perfect"),
	DashNormal UMETA(DisplayName = "Dash Nomral"),
	DashPerfect UMETA(DisplayName = "Dash Perfect"),
	PlayerHealed UMETA(DisplayName = "Player Healed"),
	PlayerDamaged UMETA(DisplayName = "Player Damaged"),
	AttackInRange UMETA(DisplayName = "Attack In Range"),
	AttackOutRange UMETA(DisplayName = "Attack Out Range"),
	PurificationFailNormal UMETA(DisplayName = "Purification Fail Normal"),
	PurificationFailDanger UMETA(DisplayName = "Purification Fail Danger"),
	DashFailed UMETA(DisplayName = "Dash Failed"),
	BossDied UMETA(DisplayName = "Boss Died"),
	MetronomeSound UMETA (DisplayName = "Metronome Sound")
};

//스테이지 타입
UENUM(BlueprintType)
enum class EStageIndex : uint8
{
	AdjustInputOffset = 200 UMETA(DisplayName = "AdjustInputOffset"),
	StageTutorial = 0 UMETA(DisplayName = "StageTutorial"),
	Stage_1_1 UMETA(DisplayName = "1-1"),
	Stage_1_2 UMETA(DisplayName = "1-2"),
	Stage_1_3 UMETA(DisplayName = "1-3"),
	Stage_2_1 UMETA(DisplayName = "2-1"),
	Stage_2_2 UMETA(DisplayName = "2-2"),
	Stage_2_3 UMETA(DisplayName = "2-3"),
	Stage_3_1 UMETA(DisplayName = "3-1"),
	Stage_3_2 UMETA(DisplayName = "3-2"),
	Stage_3_3 UMETA(DisplayName = "3-3"),
	Stage_4_1 UMETA(DisplayName = "4-1"),
	Stage_4_2 UMETA(DisplayName = "4-2"),
	Stage_4_3 UMETA(DisplayName = "4-3")
};

//판정 타입
UENUM()
enum EJudgementResult : uint16
{
	//대미지가 높은 순
	AttackPerfect = 4, 
	AttackGreat = 3, 
	AttackGood = 2, 
	AttackNormal = 1, 
	AttackFail = 0,
	//대시는 10으로
	DashPerfect = 14, 
	DashSuccess = 11, 
	DashFail = 10, 
	DashCancel = 9
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Normal UMETA(DisplayName = "Normal Attack"),
	Dash UMETA(DisplayName = "Dash Attack")
};

//액션 정보
UENUM(BlueprintType)
enum class EJudgementAction : uint8
{
	Attack UMETA(DisplayName = "Attack Action"),
	Dash UMETA(DisplayName = "Dash Action")
};

//스테이지 랭크 타입
UENUM(BlueprintType)
enum class ERankType : uint8
{
	S UMETA(DisplayName = "S Rank"),
	A UMETA(DisplayName = "A Rank"),
	B UMETA(DisplayName = "B Rank"),
	C UMETA(DisplayName = "C Rank"),
	None UMETA(DisplayName = "None Rank")
};

//점수를 얻는 상황
UENUM(BlueprintType)
enum class EScoreType : uint8
{
	KillEnemy	UMETA(DisplayName = "Kill Enemy"),
	EveryBeat	UMETA(DisplayName = "Every Beat"),
	Recover		UMETA(DisplayName = "Recover")
};

//인풋 액션의 종류
UENUM(BlueprintType)
enum class EInputAction : uint8
{
	Dash UMETA(DisplayName = "Dash Action"),
	Move UMETA(DisplayName = "Move Action"),
	Look UMETA(DisplayName = "Look Action"),
	ArrowMove UMETA(DisplayName = "Arrow Move Action"),
	Attack UMETA(DisplayName = "Attack Action"),
	Quit UMETA(DisplayName = "Quit Action"),
	Esc UMETA(DisplayName = "Esc"),
	Debug_ToggleDebugMode UMETA(DisplayName = "Toggle Debug Mode"),
	Debug_AllPerfectMode UMETA(DisplayName = "Debug : All perfect mode"),
	Debug_InfinityPurificationMode UMETA(DisplayName = "Debug : Infinity purification mode"),
	Debug_InfinityHealthAndStamina UMETA(DisplayName = "Debug : Infinity health and stemina mode"),
	Debug_Invincibility UMETA(DisplayName = "Debug : Invincibility mode"),
	Debug_FixPlayer UMETA(DisplayName = "Debug : Fix player Mode"),
	Debug_InfinityDamage UMETA(DisplayName = "Debug : Infinity damage"),
	Debug_ViewBeatIndex  UMETA(DisplayName = "Debug : View BeatIndex Log"),
	Debug_InfinityRange UMETA(DisplayName = "Debug : Infinity range"),
	//튜토리얼 전용
	InputAction_W UMETA(DisplayName = "W key OnPressed"),
	InputAction_A UMETA(DisplayName = "A key OnPressed"),
	InputAction_S UMETA(DisplayName = "S key OnPressed"),
	InputAction_D UMETA(DisplayName = "D key OnPressed")
};

UENUM(BlueprintType)
enum class ETutorialKeyType : uint8
{
	W, A, S, D
};

//디버그 모드 종류
UENUM(BlueprintType)
enum class EDebugMode : uint8
{
	DebugMode UMETA(DisplayName = "Debug Mode"),
	AllPerfect UMETA(DisplayName = "All Perfect Mode"),
	InfinityPurification UMETA(DisplayName = "Infinity Purification Mode"),
	InfinityHealthAndStamina UMETA(DisplayName = "Infinity Health And Stamina"),
	Invincibility	UMETA(DisplayName = "Invincibility Mode"),
	FixPlayer UMETA(DisplayName = "Fix Player Mode"),
	InfinityDamage UMETA(DisplayName = "Infinity Damage"),
	ViewBeatIndex UMETA(DisplayName = "View Log BeatIndex"),
	InfinityRange UMETA(DisplayName = "Infinity Range")
};

//게임 오버 타입
UENUM(BlueprintType)
enum class EGameOverType : uint8
{
	GameClear_Normal UMETA(DisplayName = "Game Clear_Normal"),
	GameClear_Boss UMETA(DisplayName = "Game Clear_Boss"),
	GameFailed_PlayerDied UMETA(DisplayName = "Game Failed_Player Died"),
	GameFailed_PurificationFailed UMETA(DisplayName = "Game Failed_Purification Failed")
};

//메뉴 타입
UENUM(BlueprintType)
enum class EMenu : uint8
{
	Intro UMETA(DisplayName = "Intro"),
	Main UMETA(DisplayName = "Main Menu"),
	HowToPlay UMETA(DisplayName = "How To Play"),
	Credit UMETA(DisplayName = "Credit"),
	Reset UMETA(DisplayName = "Reset"),
	SelectStage UMETA(DisplayName = "Select Stage"),
	StageEnterConfirm UMETA(DisplayName = "Stage Enter Confirm"),
	Story UMETA(DisplayName = "Story")
};

//메뉴 타입
UENUM(BlueprintType)
enum class EApplyDamageType : uint8
{
	Always     UMETA(DisplayName = "Always Apply Damage"),       // 항상 대미지
	OnAttack   UMETA(DisplayName = "Only When Attacking"),       // 공격 중일 때만
	Never      UMETA(DisplayName = "Do Not Apply Damage")        // 대미지 없음
};

UENUM(BlueprintType)
enum class ECommonEnemyType : uint8
{
	None			UMETA(DisplayName = "Select Enemy Type!"),
	Dummy			UMETA(DisplayName = "Dummy"),
	Test_A			UMETA(DisplayName = "For Test - A"),
	Test_B			UMETA(DisplayName = "For Test - B"),
	Test_C			UMETA(DisplayName = "For Test - C"),
	Dash_Basic		UMETA(DisplayName = "Dash Enemy - Basic type"),
	Dash_Heavy		UMETA(DisplayName = "Dash Enemy - Heavy type"),
	Dash_DashSkill	UMETA(DisplayNAme = "Dash Enemy - Dash Skill type")
};

UENUM(BlueprintType)
enum class EShootingCountPerBeat : uint8
{
	Zero	UMETA(DisplayName = "0"),
	One		UMETA(DisplayName = "1"),
	Two		UMETA(DisplayName = "2"),
	Max		UMETA(DisplayName = "Max")
};

//스테이지 기록 구조체
USTRUCT(Atomic, BlueprintType)
struct FStageRecord
{
	GENERATED_USTRUCT_BODY()
public:
	FStageRecord() : bIsClear(false), BestScore(0), BestClearStrike(0), BestPurified(0), BestCombo(0), ProgressPercent(0.0f), Rank(ERankType::None),Attempt(0) {}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsClear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BestScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BestClearStrike;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BestPurified;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BestCombo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProgressPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERankType Rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attempt;
};

//세팅 데이타 구조체
USTRUCT(Atomic, BlueprintType)
struct FSettingData
{
	GENERATED_USTRUCT_BODY()
public:
	FSettingData() : InputOffset(0), BgmVolume(10), SfxVolume(10), UIVolume(10), MetronomeVolume(10), GraphicQuality(1){}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InputOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BgmVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SfxVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UIVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MetronomeVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GraphicQuality;
};

//투사체에 대한 기본적인 정보를 담은 변수
USTRUCT(Atomic, BlueprintType)
struct FProjectileInformation
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectileInformation()
		: StartPosition(FVector(0.f, 0.f, 0.f))
		, ProjectileSpeed(0.0f)
		, ProjectileAngle(FRotator(0.f, 0.f, 0.f))
		, ProjectileRange(0.f)
	{
	}	//발사될 투사체의 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ALinearProjectile> Projectile;
	//투사체가 출발하는 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPosition;
	//투사체의 비트당 이동거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed;
	//투사체가 날라가는 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator ProjectileAngle;
	//투사체가 최초 위치로부터 최대로 날라가는 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileRange;
	//투사체의 타겟이 되는 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* TargetClass;
};

USTRUCT(Atomic, BlueprintType)
struct FProjectileSetting
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectileSetting()
	{
		Projectile = nullptr;
		Speed = 0.0f;
		Range = 0.0f;
		Angle = 0.0f;
		Delay_Beat = 0;
		Delay_QuaterBeat = 0;
		bIsUseDetailProjectile = false;
		bIsUseDetailSpeed = false;
		bIsUseDetailRange = false;
		bIsUseDetailAngle = false;
	}

	//Default Projectile를 사용할 것인지 별도의 투사체를 설정할 것인지 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailProjectile;
	//발사할 투사체의 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailProjectile"))
	TSubclassOf<class ALinearProjectile> Projectile;

	//Default Speed를 사용할 것인지 별도로 Speed를 설정할 것인지 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailSpeed;
	//투사체의 비트당 이동거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailSpeed"))
	float Speed;

	//Default Range를 사용할 것인지 별도로 Range를 설정할 것인지 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailRange;
	//투사체가 시작 지점으로부터 최대로 날라가는 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailRange"))
	float Range;

	//Default Custom Standard Of Angle를 사용할 것인지에 대한 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailCustomStandardOfAngle;
	//Custom StandardOfAngle를 사용할 것인지에 대한 여부, Default 값을 따르지 않는 경우 이 투사체에 대해서는 기준을 어떻게 할 것인지를 물어보는 것
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailCustomStandardOfAngle"))
	bool bIsUseCustomStandardOfAngle;
	//별도의 Projectile Angle의 각도를 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseCustomStandardOfAngle", EditConditionHides))
	float CustomStandardOfAngle;

	//Default Angle를 사용할 것인지에 대한 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailAngle;
	//투사체가 날라가는 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailAngle"))
	float Angle;

	//전체 디테일 사격이 시작된 때를 기준으로 몇 Beat 이후에 해당 투사체를 발사할 것인지 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Delay_Beat;
	//전체 디테일 사격이 시작된 때를 기준으로 몇 QuaterBeat 이후에 해당 투사체를 발사할 것인지 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Delay_QuaterBeat;

};

//투사체 적의 일반 사격을 설정하는 구조체
USTRUCT(Atomic, BlueprintType)
struct FProjectileNormalSetting
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectileNormalSetting()
	{
		ShootingBeatLength = 1;
		ShootingCoolTimeBeat = 0;
		ProjectileCountPerShoot = 1;
		ProjectileSpeed = 100;
		ProjectileRange = 1000;
		ProjectileAngleGap = 15.0;
		ShootingProgressBeat = -1;
		CurrentCoolTimeBeat = 0;
		bIsCoolTime = false;
		bIsStartDelay = false;
		ShootingStartDelayBeat = 0;
	}
	//사격의 지속시간 및 쿨타임을 업데이트하는 함수
	void UpdateSettingCoolTime()
	{
		if (ShootingStartDelayBeat > 0)
		{
			bIsStartDelay = true;
			bIsCoolTime = true;
			ShootingStartDelayBeat--;
			return;
		}
		else if (bIsStartDelay && ShootingStartDelayBeat == 0)
		{
			bIsStartDelay = false;
			bIsCoolTime = false;
		}
		if (!bIsCoolTime)
		{
			ShootingProgressBeat++;
		}
		else
		{
			CurrentCoolTimeBeat--;
		}
		if (!bIsCoolTime && ShootingProgressBeat >= ShootingBeatLength)
		{
			bIsCoolTime = true;
			ShootingProgressBeat = 0;
			CurrentCoolTimeBeat = ShootingCoolTimeBeat;
		}
		if (bIsCoolTime && CurrentCoolTimeBeat == 0)
		{
			bIsCoolTime = false;
			ShootingProgressBeat = 0;
			CurrentCoolTimeBeat = ShootingCoolTimeBeat;
		}
	}
	bool IsCoolTime()
	{
		return bIsCoolTime;
	}
	//비트 당 사격하는 횟수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EShootingCountPerBeat ShootingCountPerBeat;
	
	//사격을 지속하는 비트 수 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ShootingBeatLength;
	//모든 사격이 끝난 후 쿨타임 비트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ShootingCoolTimeBeat;
	//맨 처음 사격까지 기다리는 비트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ShootingStartDelayBeat;
	//사격 1회당 발사하는 총알의 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ProjectileCountPerShoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailCustomStandardOfAngle;
	//ProjectileAngle의 기준이 되는 각도를 사용할 것인지 설정, false인 경우 플레이어를 바라보는 방향이 기준
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailCustomStandardOfAngle"))
	bool bIsUseCustomStandardOfAngle;
	//사격의 기준이 되는 각도 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseCustomStandardOfAngle", EditConditionHides))
	float CustomStandardOfAngle;

	//여러 총알을 발사할 경우 총알끼리의 각도 차이
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileAngleGap;

	//사격에 사용할 투사체 설정 여부 및 투사체 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailProjectile;
	//사격에 사용할 투사체 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailProjectile"))
	TSubclassOf<class ALinearProjectile> ProjectileClass;
	//Default Projectile Speed를 쓸 것인지 아닌지 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailSpeed;
	//투사체의 비트당 이동거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailSpeed"))
	int ProjectileSpeed;
	//Default Projectile Range를 쓸 것인지 아닌지 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bIsUseDetailRange;
	//투사체가 최대로 날라가는 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsUseDetailRange"))
	int ProjectileRange;
	//현재 사격한 비트 수
	int ShootingProgressBeat;
	//현재 남은 쿨타임
	int CurrentCoolTimeBeat;
	//현재 노말 사격이 쿨타임인지 여부
	bool bIsCoolTime;
	//아직 첫 사격 딜레이인가에 대한 여부
	bool bIsStartDelay;
};
//투사체 적의 디테일 사격을 설정하는 구조체
USTRUCT(Atomic, BlueprintType)
struct FProjectileDetailSetting
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectileDetailSetting()
	{
		DetailShootingLength_Beat = 0;
		DetailShootingLength_QuaterBeat = 0;
		DetailShootingRepeatCount = 0;
		DetailShootingCoolTime_Beat = 0;
		DetailShootingCoolTime_QuaterBeat = 0;
		CurrentCoolTimeQuaterBeat = 0;
		ProgressQuaterBeat = 0;
		CurrentRepeatCount = 0;
		bIsCoolTime = false;
	}
	//디테일 사격의 지속시간 및 쿨타임을 조절하는 함수
	void UpdateSettingCoolTime(class AStageManager* StageManager);
	bool IsCoolTime()
	{
		return bIsCoolTime;
	}
	//한 번의 디테일 사격이 얼마나 걸리는지에 대한 길이(Beat)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDetailSetting", EditConditionHides))
	int DetailShootingLength_Beat;
	//한 번의 디테일 사격이 얼마나 걸리는지에 대한 길이(QuaterBeat)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDetailSetting", EditConditionHides))
	int DetailShootingLength_QuaterBeat;
	//디테일 사격의 반복 횟수
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDetailSetting", EditConditionHides))
	int DetailShootingRepeatCount;
	//반복을 마친 후 디테일 사격의 쿨타임 (Beat)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDetailSetting", EditConditionHides))
	int DetailShootingCoolTime_Beat;
	//반복을 마친 후 디테일 사격의 쿨타임 (QuaterBeat)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDetailSetting", EditConditionHides))
	int DetailShootingCoolTime_QuaterBeat;
	//디테일 슈팅 각 투사체의 정보
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDetailSetting", EditConditionHides))
	TArray<FProjectileSetting> ProjectileSettings;

	//현재 디테일 사격의 남은 쿨타임
	int CurrentCoolTimeQuaterBeat;
	//현재 디테일 사격의 진행 비트
	int ProgressQuaterBeat;
	//현재 디테일 사격의 반복 횟수
	int CurrentRepeatCount;
	//현재 디테일 사격이 쿨타임인가에 대한 여부
	bool bIsCoolTime;
};

//투사체에 대한 기본적인 정보를 담은 변수


USTRUCT(Atomic, BlueprintType)
struct FShootingPatternSetting
{
	GENERATED_USTRUCT_BODY()
public:
	FShootingPatternSetting()
	{
		bUseNormalSetting = false;
		bUseDetailSetting = false;
		ProgressBeat = 0;
	}
	
	//패턴의 길이(Beat), 나머지 설정과 무관하게 패턴이 시작한 후로 설정된 Beat + QuaterBeat만큼 비트가 지나면 다음 패턴을 실행한다.
	UPROPERTY(EditAnywhere)
	int PatternLength_Beat;
	//패턴의 길이(QuaterBeat), 나머지 설정과 무관하게 패턴이 시작한 후로 설정된 Beat + QuaterBeat만큼 비트가 지나면 다음 패턴을 실행한다.
	UPROPERTY(EditAnywhere)
	int PatternLegnth_QuaterBeat;
	//이전 패턴과 함께 실행할 것인지에 대한 여부, 이를 활성화 할 경우 이전 패턴과 함께 실행하며 이전 패턴이 종료될 때 함께 종료된다.
	UPROPERTY(EditAnywhere)
	bool bExecuteConcurrentWithPrevious;
	//일반 슈팅 사용
	UPROPERTY(EditAnywhere)
	bool bUseNormalSetting;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseNormalSetting", EditConditionHides))
	FProjectileNormalSetting ProjectileNormalSetting;
	//디테일 슈팅 사용
	UPROPERTY(EditAnywhere)
	bool bUseDetailSetting;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseDetailSetting", EditConditionHides))
	FProjectileDetailSetting ProjectileDetailSetting;

	//현재 패턴이 진행 중인 비트수
	int ProgressBeat;

};


/**
 * 
 */
class UCISMA_API CommonTypes
{
public:
	CommonTypes();
	~CommonTypes();
};