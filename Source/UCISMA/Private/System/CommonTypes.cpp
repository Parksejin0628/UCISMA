// Fill out your copyright notice in the Description page of Project Settings.


#include "System/CommonTypes.h"
#include "Manager/StageManager.h"

CommonTypes::CommonTypes()
{
}

CommonTypes::~CommonTypes()
{
}

void FProjectileDetailSetting::UpdateSettingCoolTime(AStageManager* StageManager)
{
	if (CurrentCoolTimeQuaterBeat > 0)
	{
		CurrentCoolTimeQuaterBeat--;
	}
	if (CurrentCoolTimeQuaterBeat != 0)
	{
		return;
	}

	ProgressQuaterBeat++;
	
	if (ProgressQuaterBeat >= DetailShootingLength_Beat * StageManager->GetBeatUpdateCallRate() + DetailShootingLength_QuaterBeat)
	{
		ProgressQuaterBeat = 0;
		CurrentRepeatCount++;
	}
	if (CurrentRepeatCount >= DetailShootingRepeatCount)
	{
		CurrentCoolTimeQuaterBeat = DetailShootingCoolTime_Beat * StageManager->GetBeatUpdateCallRate();
		CurrentCoolTimeQuaterBeat += DetailShootingCoolTime_QuaterBeat;
		CurrentRepeatCount = 0;
	}
	bIsCoolTime = (CurrentCoolTimeQuaterBeat > 0);
}