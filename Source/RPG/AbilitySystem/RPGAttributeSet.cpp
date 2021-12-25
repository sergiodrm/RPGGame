#include "RPGAttributeSet.h"
#include "GameplayEffectExtension.h"

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxHealth());
    }
    else if (Attribute == GetStaminaAttribute())
    {
        NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxStamina());
    }
    else if (Attribute == GetMagicAttribute())
    {
        NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxMagic());
    }
}
