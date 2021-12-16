#include "RPGAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffectExtension.h"

static float Clamp(float value, float min, float max)
{
    return value <= min ? min : value <= max ? value : max;
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }
    else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
    {
        SetStamina(Clamp(GetStamina(), 0.f, GetMaxStamina()));
    }
}
