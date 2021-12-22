#include "RPGAbilityTask_PlayMontageAndWaitInput.h"
#include "RPG/RPG.h"
#include "AbilitySystemComponent.h"

URPGAbilityTask_PlayMontageAndWaitInput* URPGAbilityTask_PlayMontageAndWaitInput::CreatePlayMontageAndWaitInputProxy(UGameplayAbility* owningAbility, FName taskInstanceName, UAnimMontage* montageToPlay, FName startSection)
{
    URPGAbilityTask_PlayMontageAndWaitInput* task = NewAbilityTask<URPGAbilityTask_PlayMontageAndWaitInput>(owningAbility, taskInstanceName);
    task->AnimMontage = montageToPlay;
    task->StartSection = startSection;
    return task;
}

void URPGAbilityTask_PlayMontageAndWaitInput::Activate()
{
    Super::Activate();

    bool montagePlayed {false};
    if (Ability && AbilitySystemComponent)
    {
        const FGameplayAbilityActorInfo* actorInfo = Ability->GetCurrentActorInfo();
        if (UAnimInstance* animInstance = actorInfo ? actorInfo->GetAnimInstance() : nullptr)
        {
            if (AbilitySystemComponent->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), AnimMontage, 1.f, StartSection) > 0.f)
            {
                if (ShouldBroadcastAbilityTaskDelegates())
                {
                    CanceledHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &URPGAbilityTask_PlayMontageAndWaitInput::OnMontageInterrupted);

                    MontageBlendingOutDelegate.BindUObject(this, &URPGAbilityTask_PlayMontageAndWaitInput::OnMontageBlendingOut);
                    animInstance->Montage_SetBlendingOutDelegate(MontageBlendingOutDelegate, AnimMontage);

                    MontageEndedDelegate.BindUObject(this, &URPGAbilityTask_PlayMontageAndWaitInput::OnMontageEnded);
                    animInstance->Montage_SetEndDelegate(MontageEndedDelegate, AnimMontage);

                    montagePlayed = true;
                }
            }
        }
    }

    if (!montagePlayed)
    {
        RPG_LOG(Warning, TEXT("AbilityTask_PlayMontageAndWaitInput couldn't play the montage specified"));
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            OnMontageCanceled.Broadcast();
        }
    }
}

void URPGAbilityTask_PlayMontageAndWaitInput::OnDestroy(bool bInOwnerFinished)
{
    if (Ability)
    {
        Ability->OnGameplayAbilityCancelled.Remove(CanceledHandle);
    }
    Super::OnDestroy(bInOwnerFinished);
}

void URPGAbilityTask_PlayMontageAndWaitInput::ExternalCancel()
{
    if (StopPlayingMontage())
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            OnMontageCanceled.Broadcast();
        }
    }
    Super::ExternalCancel();
}

void URPGAbilityTask_PlayMontageAndWaitInput::OnMontageInterrupted()
{
    const bool stoppedSuccessfully = StopPlayingMontage();
    if (ShouldBroadcastAbilityTaskDelegates() && stoppedSuccessfully)
    {
        OnMontageCanceled.Broadcast();
    }
}

void URPGAbilityTask_PlayMontageAndWaitInput::OnMontageBlendingOut(UAnimMontage* animMontage, bool interrupted)
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        if (interrupted)
        {
            OnMontageCanceled.Broadcast();
        }
        else
        {
            OnMontageBlendOut.Broadcast();
        }
    }
}

void URPGAbilityTask_PlayMontageAndWaitInput::OnMontageEnded(UAnimMontage* animMontage, bool interrupted)
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        if (!interrupted)
        {
            OnMontageCompleted.Broadcast();
        }
    }
    EndTask();
}

bool URPGAbilityTask_PlayMontageAndWaitInput::StopPlayingMontage()
{
    bool success = false;
    const FGameplayAbilityActorInfo* actorInfo = Ability->GetCurrentActorInfo();
    if (UAnimInstance* animInstance = actorInfo ? actorInfo->GetAnimInstance() : nullptr)
    {
        if (AbilitySystemComponent
            && AbilitySystemComponent->GetAnimatingAbility() == Ability
            && AbilitySystemComponent->GetCurrentMontage() == AnimMontage)
        {
            if (FAnimMontageInstance* animMontageInstance = animInstance->GetActiveInstanceForMontage(AnimMontage))
            {
                animMontageInstance->OnMontageBlendingOutStarted.Unbind();
                animMontageInstance->OnMontageEnded.Unbind();
            }
            AbilitySystemComponent->CurrentMontageStop();
            success = true;
        }
    }
    return success;
}
