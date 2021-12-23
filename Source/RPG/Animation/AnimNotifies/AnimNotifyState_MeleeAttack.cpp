#include "AnimNotifyState_MeleeAttack.h"

#include "RPG/Character/RPGCharacter.h"

UAnimNotifyState_MeleeAttack::UAnimNotifyState_MeleeAttack()
{ }

void UAnimNotifyState_MeleeAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);
    ARPGCharacter* character = MeshComp ? MeshComp->GetOwner<ARPGCharacter>() : nullptr;
    if (character)
    {
        character->BeginHandleMeleeAttack();
    }
}

void UAnimNotifyState_MeleeAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    ARPGCharacter* character = MeshComp ? MeshComp->GetOwner<ARPGCharacter>() : nullptr;
    if (character)
    {
        character->EndHandleMeleeAttack();
    }
}
