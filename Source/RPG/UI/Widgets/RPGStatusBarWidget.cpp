#include "RPGStatusBarWidget.h"

#include "Components/ProgressBar.h"
#include "RPG/Character/RPGCharacter.h"

void URPGStatusBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (UWorld* world = GetWorld())
    {
        APlayerController* controller = world->GetFirstPlayerController();
        ARPGCharacter* character = controller ? controller->GetPawn<ARPGCharacter>() : nullptr;
        if (character)
        {
            character->OnHealthAttributeChangedDelegate.AddUObject(this, &URPGStatusBarWidget::OnHealthChanged);
            character->OnStaminaAttributeChangedDelegate.AddUObject(this, &URPGStatusBarWidget::OnStaminaChanged);
            character->OnMagicAttributeChangedDelegate.AddUObject(this, &URPGStatusBarWidget::OnMagicChanged);
        }
    }
}

void URPGStatusBarWidget::OnHealthChanged(float oldValue, float newValue, float maxValue)
{
    SetHealthPercentage(newValue / maxValue);
}

void URPGStatusBarWidget::OnStaminaChanged(float oldValue, float newValue, float maxValue)
{
    SetStaminaPercentage(newValue / maxValue);
}

void URPGStatusBarWidget::OnMagicChanged(float oldValue, float newValue, float maxValue)
{
    SetMagicPercentage(newValue / maxValue);
}

void URPGStatusBarWidget::SetHealthPercentage(float healthPercentage)
{
    HealthBar->SetPercent(healthPercentage);
}

void URPGStatusBarWidget::SetStaminaPercentage(float staminaPercentage)
{
    StaminaBar->SetPercent(staminaPercentage);
}

void URPGStatusBarWidget::SetMagicPercentage(float magicPercentage)
{
    MagicBar->SetPercent(magicPercentage);
}
