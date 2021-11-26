#pragma once
#include "CoreMinimal.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

USTRUCT()
struct FRPGCharacterInputActions
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Transient)
    class UInputAction* MovementAction;
    UPROPERTY(EditDefaultsOnly, Transient)
    class UInputAction* JumpAction;
    UPROPERTY(EditDefaultsOnly, Transient)
    class UInputAction* LookAction;
};

UCLASS()
class ARPGCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ARPGCharacter();
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    bool IsJumping() const;
protected:
    UFUNCTION()
    void OnMovementAction(const FInputActionValue& actionValue);
    UFUNCTION()
    void OnStartJumpAction(const FInputActionValue& actionValue);
    UFUNCTION()
    void OnEndJumpAction(const FInputActionValue& actionValue);
    UFUNCTION()
    void OnLookAction(const FInputActionValue& actionValue);

public:
    UPROPERTY(EditDefaultsOnly)
    FRPGCharacterInputActions InputActions;
    UPROPERTY(EditDefaultsOnly, Transient)
    class UInputMappingContext* InputMapping;
private:
    UPROPERTY(VisibleAnywhere, Transient)
    class USkeletalMeshComponent* SkeletalMeshComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class UStaticMeshComponent* WeaponMeshComponent;

    UPROPERTY(VisibleAnywhere, Transient)
    class USpringArmComponent* SpringArmComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class UCameraComponent* CameraComponent;
};
