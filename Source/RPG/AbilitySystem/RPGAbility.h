#pragma once

#include "CoreMinimal.h"

#include "Abilities/GameplayAbility.h"

#include "RPGAbility.generated.h"

UCLASS(BlueprintType)
class URPGAbility : public UGameplayAbility
{
    GENERATED_BODY()
public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    FORCEINLINE virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; }
};
