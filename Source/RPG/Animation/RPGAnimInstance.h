#pragma once

#include "CoreMinimal.h"
#include "RPGAnimInstance.generated.h"

UCLASS(Blueprintable)
class URPGAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeBeginPlay() override;

    UFUNCTION(BlueprintCallable)
    FVector GetMovementDirection() const;

    UFUNCTION(BlueprintCallable)
    float GetForwardSpeed() const;

private:
    UPROPERTY(Transient)
    class ARPGCharacter* OwnerCharacter;
};
