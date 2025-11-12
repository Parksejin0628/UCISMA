// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeatUnit/BeatUnitActor.h"
#include "BeatUnitActor_LoopTile.generated.h"

/**
 * 
 */
UCLASS()
class UCISMA_API ABeatUnitActor_LoopTile : public ABeatUnitActor
{
	GENERATED_BODY()
	
public:
	ABeatUnitActor_LoopTile();

protected:
	virtual void BeginPlay() override;
	virtual void ActiveUnit() override;
	virtual void DeactiveUnit() override;

};




