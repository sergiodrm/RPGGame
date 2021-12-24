#include "RPGAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffectExtension.h"

static float Clamp(float value, float min, float max)
{
    return value <= min ? min : value >= max ? max : value;
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
}

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    if (Attribute == GetHealthAttribute())
    {
        NewValue = Clamp(NewValue, 0.f, GetMaxHealth());
    }
    else if (Attribute == GetStaminaAttribute())
    {
        NewValue = Clamp(NewValue, 0.f, GetMaxStamina());
    }
    else if (Attribute == GetMagicAttribute())
    {
        NewValue = Clamp(NewValue, 0.f, GetMaxMagic());
    }
}
