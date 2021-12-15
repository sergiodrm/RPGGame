#pragma once
#include "CoreMinimal.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
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

    UPROPERTY(EditDefaultsOnly, Transient)
    class UInputAction* BlockAction;
};

UCLASS(BlueprintType)
class ARPGCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()
public:
    ARPGCharacter();
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void PossessedBy(AController* NewController) override;

    bool IsJumping() const;
    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool IsBlocking() const { return Blocking; }

    /** Begin IAbilitySystemInterface methods */
    FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
    /** End IAbilitySystemInterface methods */

protected:
    UFUNCTION()
    void OnStartJump();
    UFUNCTION()
    void OnEndJump();
    UFUNCTION()
    void OnMoveForward(float value);
    UFUNCTION()
    void OnMoveRight(float value);
    UFUNCTION()
    void LookUp(float value);
    UFUNCTION()
    void Turn(float value);

    virtual void InitializeAttributes();
    virtual void InitializeAbilities();

public:
    UPROPERTY(EditDefaultsOnly)
    FRPGCharacterInputActions InputActions;
    UPROPERTY(EditDefaultsOnly, Transient)
    class UInputMappingContext* InputMapping;
    UPROPERTY(EditDefaultsOnly, Transient)
    TSubclassOf<class URPGGameplayAbility> Ability;
    UPROPERTY(EditDefaultsOnly, Transient)
    TSubclassOf<class UGameplayEffect> DefaultAbilityEffect;
private:
    UPROPERTY(VisibleAnywhere, Transient)
    class USkeletalMeshComponent* SwordMeshComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class UStaticMeshComponent* ShieldStaticMeshComponent;

    UPROPERTY(VisibleAnywhere, Transient)
    class USpringArmComponent* SpringArmComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, Transient)
    class UAbilitySystemComponent* AbilitySystemComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class URPGAttributeSet* RPGAttributeSet;

    bool Blocking {false};
};
