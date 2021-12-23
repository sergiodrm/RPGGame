#include "RPGGameplayAbility.h"
#include "Animation/AnimInstance.h"
#include "RPG/Character/RPGCharacter.h"

void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (BlockMovementWhileExecution)
    {
        if (ARPGCharacter* character = Cast<ARPGCharacter>(ActorInfo->AvatarActor.Get()))
        {
            character->BlockMovement(true);
        }
    }
}

void URPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
    if (BlockMovementWhileExecution)
    {
        if (ARPGCharacter* character = Cast<ARPGCharacter>(ActorInfo->AvatarActor.Get()))
        {
            character->BlockMovement(false);
        }
    }
}
