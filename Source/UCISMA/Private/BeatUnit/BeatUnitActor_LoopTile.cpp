// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatUnit/BeatUnitActor_LoopTile.h"


ABeatUnitActor_LoopTile::ABeatUnitActor_LoopTile() {
}
void ABeatUnitActor_LoopTile::DeactiveUnit() {
    Super::DeactiveUnit();
}
void ABeatUnitActor_LoopTile::BeginPlay() {
    Super::BeginPlay();
    SetActorHiddenInGame(false);  // 화면에는 보이게
    SetActorTickEnabled(false);   // Tick은 끔
}
void ABeatUnitActor_LoopTile::ActiveUnit()
{
    Super::ActiveUnit();
}