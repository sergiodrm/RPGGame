#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_MeleeAttack.generated.h"

UCLASS()
class UAnimNotifyState_MeleeAttack : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    UAnimNotifyState_MeleeAttack();

    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
