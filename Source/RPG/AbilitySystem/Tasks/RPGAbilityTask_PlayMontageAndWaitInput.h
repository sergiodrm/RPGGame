#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "RPGAbilityTask_PlayMontageAndWaitInput.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayMontageDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitInputDelegate);


UCLASS()
class URPGAbilityTask_PlayMontageAndWaitInput : public UAbilityTask
{
    GENERATED_BODY()
    /**
     * @brief Create an instance of the task. On activation, the task will play the montage specified and will be listening
     * the input associated with the ability.
     * @param owningAbility The ability which is being executed.
     * @param taskInstanceName The name associated with the instanced task.
     * @param montageToPlay The montage to play.
     * @param startSection Which section of the montage will be start point.
    */
    UFUNCTION(BlueprintCallable, Category = "RPG|Ability|Tasks",
        meta = (HidePin = "owningAbility", DefaultToSelf = "owningAbility", BlueprintInternalUseOnly = "TRUE"))
    static URPGAbilityTask_PlayMontageAndWaitInput* CreatePlayMontageAndWaitInputProxy(UGameplayAbility* owningAbility,
                                                                                       FName taskInstanceName,
                                                                                       UAnimMontage* montageToPlay,
                                                                                       FName startSection = NAME_None);


    virtual void Activate() override;
    virtual void OnDestroy(bool bInOwnerFinished) override;
    virtual void ExternalCancel() override;


protected:
    UFUNCTION()
    void OnMontageInterrupted();
    UFUNCTION()
    void OnMontageBlendingOut(UAnimMontage* animMontage, bool interrupted);
    UFUNCTION()
    void OnMontageEnded(UAnimMontage* animMontage, bool interrupted);

    bool StopPlayingMontage();

    UFUNCTION()
        void OnInputPressed();
    UFUNCTION()
        void OnInputReleased();

public:
    UPROPERTY(BlueprintAssignable)
    FPlayMontageDelegate OnMontageCompleted;
    UPROPERTY(BlueprintAssignable)
    FPlayMontageDelegate OnMontageBlendOut;
    UPROPERTY(BlueprintAssignable)
    FPlayMontageDelegate OnMontageCanceled;
    UPROPERTY(BlueprintAssignable)
    FWaitInputDelegate OnInputPress;
    UPROPERTY(BlueprintAssignable)
    FWaitInputDelegate OnInputRelease;

private:
    UPROPERTY(Transient)
    class UAnimMontage* AnimMontage;
    UPROPERTY()
    FName StartSection;

    FOnMontageBlendingOutStarted MontageBlendingOutDelegate;
    FOnMontageEnded MontageEndedDelegate;
    FDelegateHandle CanceledHandle;

    FDelegateHandle InputPressHandle;
    FDelegateHandle InputReleaseHandle;
};
