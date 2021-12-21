#pragma once
#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "RPGCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FHealthAttributeChangedDelegate, float, float, float);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FStaminaAttributeChangedDelegate, float, float, float);


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

    UFUNCTION(BlueprintCallable)
    void BlockMovement(bool blocked) { MovementBlocked = blocked; }

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
    UPROPERTY(EditDefaultsOnly, Transient, Category = "Gameplay Abilities")
    TArray<TSubclassOf<class URPGGameplayAbility>> Abilities;
    UPROPERTY(EditDefaultsOnly, Transient, Category = "Gameplay Abilities")
    TArray<TSubclassOf<class UGameplayEffect>> StartupGameplayEffects;

    // Delegates
    FHealthAttributeChangedDelegate OnHealthAttributeChangedDelegate;
    FStaminaAttributeChangedDelegate OnStaminaAttributeChangedDelegate;

private:
    UPROPERTY(VisibleAnywhere, Transient)
    class USpringArmComponent* SpringArmComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, Transient)
    class UAbilitySystemComponent* AbilitySystemComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class URPGAttributeSet* RPGAttributeSet;

    bool Blocking {false};
    bool MovementBlocked {false};
};
