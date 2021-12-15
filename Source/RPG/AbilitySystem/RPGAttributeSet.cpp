#include "RPGAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffectExtension.h"

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp<float>(GetHealth(), 0.f, GetMaxHealth()));
    }
    else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
    {
        SetStamina(FMath::Clamp<float>(GetStamina(), 0.f, GetMaxStamina()));
    }
}
