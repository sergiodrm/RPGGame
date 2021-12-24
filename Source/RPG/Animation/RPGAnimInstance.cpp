#include "RPGAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "RPG/Character/RPGCharacter.h"


void URPGAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    OwnerCharacter = Cast<ARPGCharacter>(GetOwningActor());
}

FVector URPGAnimInstance::GetMovementDirection() const
{
    return OwnerCharacter->GetLastMovementInputVector();
}

float URPGAnimInstance::GetForwardSpeed() const
{
    return OwnerCharacter ? OwnerCharacter->GetVelocity().SizeSquared() : 0.f;
}
