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
    FORCEINLINE virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; }
protected:
    UFUNCTION(BlueprintImplementableEvent)
    void FinishAbilityMontage();
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    ERPGAbilityInput AbilityInput {ERPGAbilityInput::None};
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    UAnimMontage* AbilityAnimationMontage;
};
