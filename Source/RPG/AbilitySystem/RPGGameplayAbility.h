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
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

    FORCEINLINE virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; }
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    bool BlockMovementWhileExecution {false};
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Input")
    ERPGAbilityInput AbilityInput {ERPGAbilityInput::None};
};
