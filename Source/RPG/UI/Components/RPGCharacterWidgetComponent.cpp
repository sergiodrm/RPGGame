#include "RPGCharacterWidgetComponent.h"

#include "RPG/Character/RPGCharacter.h"
#include "RPG/UI/Widgets/RPGFloatingBarStatusWidget.h"

void URPGCharacterWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    FloatingWidget = Cast<URPGFloatingBarStatusWidget>(GetWidget());

    if (ARPGCharacter* character = GetOwner<ARPGCharacter>())
    {
        character->OnHealthAttributeChangedDelegate.AddUObject(this, &URPGCharacterWidgetComponent::OnCharacterHealthChanged);
    }
}

void URPGCharacterWidgetComponent::OnCharacterHealthChanged(float oldValue, float newValue, float maxValue)
{
    if (FloatingWidget)
    {
        FloatingWidget->SetHealthBarPercent(newValue / maxValue);
    }
}
