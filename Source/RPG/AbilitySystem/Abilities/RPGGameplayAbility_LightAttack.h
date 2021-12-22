#pragma once

#include "CoreMinimal.h"
#include "RPG/AbilitySystem/RPGGameplayAbility.h"
#include "RPGGameplayAbility_LightAttack.generated.h"

UCLASS(BlueprintType)
class URPGGameplayAbility_LightAttack : public URPGGameplayAbility
{
    GENERATED_BODY()
public:
    URPGGameplayAbility_LightAttack();

    /** Begin UGameplayAbility interface */
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    /** End UGameplayAbility interface */

protected:
    UFUNCTION()
    void OnMontageBlendedOut();
private:
    //UPROPERTY(Transient)
    //class URPGAbilityTask_PlayMontageAndWaitInput* PlayMontageAndWaitInputTask;
};
