#include "RPGGameplayAbility.h"
#include "Animation/AnimInstance.h"

void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Ability!"));
    }

    if (AbilityAnimationMontage)
    {
        const FGameplayAbilityActorInfo actorInfo = GetActorInfo();
        if (UAnimInstance* animInstance = actorInfo.GetAnimInstance())
        {
            animInstance->Montage_Play(AbilityAnimationMontage);

            FOnMontageEnded montageEndDelegate;
            montageEndDelegate.BindLambda([&](UAnimMontage*, bool)
            {
                GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Green, TEXT("Finish montage"));
                //EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
                FinishAbilityMontage();
            });
            animInstance->Montage_SetEndDelegate(montageEndDelegate, AbilityAnimationMontage);
        }
    }
}
