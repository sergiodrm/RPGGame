#pragma once

#include "CoreMinimal.h"
#include "RPG/Character/RPGCharacter.h"
#include "RPGPlayerCharacter.generated.h"

UCLASS()
class ARPGPlayerCharacter : public ARPGCharacter
{
    GENERATED_BODY()

public:
    ARPGPlayerCharacter();

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    UFUNCTION()
    void OnMoveForward(float value);
    UFUNCTION()
    void OnMoveRight(float value);
    UFUNCTION()
    void LookUp(float value);
    UFUNCTION()
    void Turn(float value);

protected:
    UPROPERTY(VisibleAnywhere, Transient)
    class USpringArmComponent* SpringArmComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class UCameraComponent* CameraComponent;
};
