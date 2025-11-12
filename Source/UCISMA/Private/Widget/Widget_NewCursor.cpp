// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Widget_NewCursor.h"
#include "Components/Image.h"
#include "TimerManager.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Manager/StageManager.h"

FTimerHandle CursorTimer;


void UWidget_NewCursor::NativeConstruct()
{
    Super::NativeConstruct();
    InitColor();
    InitPlayerData();
    InitData();
}

void UWidget_NewCursor::InitColor()
{
    decrease_color = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f); // R = 1, G = 0, B = 0, A = 1 (������)
    increase_color = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f); // R = 0, G = 1, B = 0, A = 1 (������)
    delete_color = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f); // R = 0, G = 0, B = 0, A = 0 (���� ����)
    default_color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void UWidget_NewCursor::InitPlayerData()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!PlayerController)
    {
        return;
    }
    PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetCharacter());
    if (!PlayerCharacter)
    {
        return;
    }

    beatsecond = PlayerCharacter->beatpersecond;
    //PlayerCharacter->OnStatsChanged.AddDynamic(this, &UWiget_State::HandleStatsChanged);
    PlayerCharacter->OnHPChanged.AddDynamic(this, &UWidget_NewCursor::HandleStatsChanged);
    Update_Health(PlayerCharacter);
    Update_Dash(PlayerCharacter);
}

void UWidget_NewCursor::InitData()
{
    bIsHealFading = false;
    HealingCellIndex = -1;
    HealFadeAlpha = 1.1f;
    DashFadeAlpha = 1.1f;
}

void UWidget_NewCursor::NativeDestruct()
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);
    }

    Super::NativeDestruct();
}


void UWidget_NewCursor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    if (!PlayerCharacter)
    {
        return;
    }
    if (!bisfading) {
        Update_Health(PlayerCharacter);
    }
    FadeHeal(InDeltaTime);

    //대쉬
    Update_Dash(PlayerCharacter);
    if (bIsDashTrans && Dash_Bar)
    {
        DashFadeAlpha += InDeltaTime * PlayerCharacter->GetStageManager()->GetBeatPerSecond();
        FLinearColor NewColor = FMath::Lerp(DashStartColor, DashTargetColor, DashFadeAlpha);
        Dash_Bar->SetPercent(1.0f);
        Dash_Bar->SetFillColorAndOpacity(NewColor);

        if (DashFadeAlpha >= 1.0f)
        {
            bIsDashTrans = false;
        }
    }
}

void UWidget_NewCursor::FadeHeal(float TickDeltaTime)
{
    if (!bIsHealFading)
    {
        return;
    }

    UProgressBar* TargetWidget = nullptr;
    if (HealingCellIndex == 1)
    {
        TargetWidget = Health_Bar_3;
    }
    else if (HealingCellIndex == 2)
    {
        TargetWidget = Health_Bar_2;
    }
    else if (HealingCellIndex == 3)
    {
        TargetWidget = Health_Bar_1;
    }
    if (!TargetWidget)
    {
        LOG_DEBUG(Error, TEXT("New Cursor Can't Find HealingCellIndex"));
        return;
    }

    HealFadeAlpha += TickDeltaTime * PlayerCharacter->GetStageManager()->GetBeatPerSecond();
    FLinearColor NewColor = FMath::Lerp(increase_color, default_color, HealFadeAlpha);
    TargetWidget->SetPercent(1.0f);
    TargetWidget->SetFillColorAndOpacity(NewColor);

    if (HealFadeAlpha > 1.0f)
    {
        bIsHealFading = false;
    }

}

void UWidget_NewCursor::Event_Increase(int HP) {
    switch (HP) {
    case 1:
        Update_Health(PlayerCharacter);
        bIsHealFading = true;
        HealFadeAlpha = 0.0f;
        HealingCellIndex = 1;
        break;
    case 2:
        Update_Health(PlayerCharacter);
        bIsHealFading = true;
        HealFadeAlpha = 0.0f;
        HealingCellIndex = 2;
        break;
    case 3:
        Update_Health(PlayerCharacter);
        bIsHealFading = true;
        HealFadeAlpha = 0.0f;
        HealingCellIndex = 3;
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Unexpected HP value in Event_Increase: %d"), HP);
        break;
    }
}
void UWidget_NewCursor::Event_Decrease(int HP) {
    switch (HP) {
    case 0:
        Update_Health(PlayerCharacter);
        bIsHealFading = false;
        HealFadeAlpha = 1.1f;
        break;
    case 1:
        Update_Health(PlayerCharacter);
        bIsHealFading = false;
        HealFadeAlpha = 1.1f;
        break;
    case 2:
        Update_Health(PlayerCharacter);
        bIsHealFading = false;
        HealFadeAlpha = 1.1f;
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Unexpected HP value in Event_Decrease: %d"), HP);
        break;
    }


}

void UWidget_NewCursor::HandleStatsChanged(int Player_Current_HP, int changer)
{
    if (changer == 1)
    {
        Event_Increase(Player_Current_HP);
    }
    else
    {

        if (bisfading) {
            bisattacked = true;
        }

        Event_Decrease(Player_Current_HP);
    }
}

void UWidget_NewCursor::Update_Health(APlayerCharacter* InPlayerCharacter)
{
    //if (InPlayerCharacter && !Health_Bar_1 && !Health_Bar_2 && !Health_Bar_3)
    if (InPlayerCharacter)
    {
        int player_hp = InPlayerCharacter->Player_Current_HP;
        
        switch (player_hp) {
        case 0:
            Health_Bar_1->SetFillColorAndOpacity(delete_color);
            Health_Bar_2->SetFillColorAndOpacity(delete_color);
            Health_Bar_3->SetFillColorAndOpacity(increase_color);
            Health_Bar_3->SetPercent(InPlayerCharacter->Player_Current_Health / InPlayerCharacter->Player_MAX_Health);
            break;
        case 1:
            Health_Bar_1->SetFillColorAndOpacity(delete_color);
            Health_Bar_2->SetFillColorAndOpacity(increase_color);
            Health_Bar_3->SetFillColorAndOpacity(default_color);
            Health_Bar_2->SetPercent(InPlayerCharacter->Player_Current_Health / InPlayerCharacter->Player_MAX_Health);
            break;
        case 2:
            Health_Bar_1->SetFillColorAndOpacity(increase_color);
            Health_Bar_2->SetFillColorAndOpacity(default_color);
            Health_Bar_3->SetFillColorAndOpacity(default_color);
            Health_Bar_1->SetPercent(InPlayerCharacter->Player_Current_Health / InPlayerCharacter->Player_MAX_Health);
            break;
        case 3:
            Health_Bar_1->SetFillColorAndOpacity(default_color);
            Health_Bar_2->SetFillColorAndOpacity(default_color);
            Health_Bar_3->SetFillColorAndOpacity(default_color);

            Health_Bar_1->SetPercent(1.0f);
            Health_Bar_2->SetPercent(1.0f);
            Health_Bar_3->SetPercent(1.0f);

        }

    }
}

void UWidget_NewCursor::Update_Dash(APlayerCharacter* InPlayerCharacter)
{
    if (Dash_Bar && InPlayerCharacter)
    {
        float CurrentStamina = InPlayerCharacter->Player_Current_Stamina;
        float MaxStamina = InPlayerCharacter->Player_MAX_Stamina;

        Dash_Bar->SetPercent(CurrentStamina / MaxStamina);

        // 100 미만으로 떨어졌을 때 → 즉시 파란색
        if (LastStamina == 100.0f && CurrentStamina < 100.0f)
        {
            Dash_Bar->SetFillColorAndOpacity(FLinearColor(0.0f, 0.5f, 1.0f, 1.0f));
            bIsDashTrans = false; // 이전 트랜지션 중지
        }

        // 다시 100이 되었을 때 → 부드럽게 흰색으로 전환
        if (CurrentStamina == 100.0f && LastStamina < 100.0f)
        {
            DashTargetColor = FLinearColor::White;
            ElapsedTime_Dash = 0.0f;
            bIsDashTrans = true;
        }

        LastStamina = CurrentStamina;
    }
}




void UWidget_NewCursor::HP_Refresh(int Player_Current_HP) {
    
}

