#pragma once
#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "RPGCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedDelegate, float, float, float);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitMeleeAttackDelegate, AActor*, hitActor);


UCLASS(BlueprintType)
class ARPGCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()
public:
    ARPGCharacter();
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    bool IsJumping() const;
    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool IsBlocking() const { return Blocking; }

    UFUNCTION(BlueprintCallable)
    void BlockMovement(bool blocked) { MovementBlocked = blocked; }

    UFUNCTION(BlueprintCallable)
    void BeginHandleMeleeAttack();
    UFUNCTION(BlueprintCallable)
    void EndHandleMeleeAttack();

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

    UFUNCTION()
    void OnMeleeAttackBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                               AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp,
                                               int32 OtherBodyIndex,
                                               bool bFromSweep,
                                               const FHitResult& SweepResult);

    virtual void InitializeAttributes();
    virtual void InitializeAbilities();

public:
    UPROPERTY(EditDefaultsOnly, Transient, Category = "Gameplay Abilities")
    TArray<TSubclassOf<class URPGGameplayAbility>> Abilities;
    UPROPERTY(EditDefaultsOnly, Transient, Category = "Gameplay Abilities")
    TArray<TSubclassOf<class UGameplayEffect>> StartupGameplayEffects;

    // Delegates
    FAttributeChangedDelegate OnHealthAttributeChangedDelegate;
    FAttributeChangedDelegate OnStaminaAttributeChangedDelegate;
    UPROPERTY(BlueprintAssignable)
    FHitMeleeAttackDelegate OnHitMeleeAttackDelegate;

private:
    UPROPERTY(VisibleAnywhere, Transient)
    class USpringArmComponent* SpringArmComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class UCameraComponent* CameraComponent;
    UPROPERTY(VisibleAnywhere, Transient)
    class UBoxComponent* MeleeAttackBoxComponent;

    UPROPERTY(VisibleAnywhere, Transient)
    class UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, Transient)
    class URPGAttributeSet* RPGAttributeSet;

    bool Blocking {false};
    bool MovementBlocked {false};
};
