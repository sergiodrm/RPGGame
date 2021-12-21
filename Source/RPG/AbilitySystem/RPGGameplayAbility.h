#pragma once

#include "CoreMinimal.h"

#include "Abilities/GameplayAbility.h"
#include "RPG/RPG.h"
#include "RPGGameplayAbility.generated.h"

UCLASS(BlueprintType)
class URPGGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()
public:
    FORCEINLINE virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; }
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    ERPGAbilityInput AbilityInput {ERPGAbilityInput::None};
};
