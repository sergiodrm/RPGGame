#include "RPGCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPG/RPG.h"
#include "RPG/AbilitySystem/Abilities/RPGGameplayAbility.h"
#include "RPG/AbilitySystem/RPGAttributeSet.h"
#include "RPG/UI/Components/RPGCharacterWidgetComponent.h"

ARPGCharacter::ARPGCharacter()
{
    bUseControllerRotationYaw = false;

    UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
    capsuleComponent->SetCapsuleHalfHeight(96.f);
    capsuleComponent->SetCapsuleRadius(42.f);

    if (USkeletalMeshComponent* mesh = GetMesh())
    {
        mesh->SetupAttachment(RootComponent);
        mesh->SetRelativeLocation({0.f, 0.f, -capsuleComponent->GetScaledCapsuleHalfHeight()});
        mesh->SetRelativeRotation({0.f, -90.f, 0.f});

        MeleeAttackBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeAttackBoxComponent"));
        MeleeAttackBoxComponent->SetupAttachment(mesh, TEXT("MeleeBoxColliderSocket"));
        MeleeAttackBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARPGCharacter::OnMeleeAttackBoxComponentBeginOverlap);
        MeleeAttackBoxComponent->SetGenerateOverlapEvents(false);
    }

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
    AbilitySystemComponent->SetIsReplicated(false);

    RPGAttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("RGPAttributeSet"));

    WidgetComponent = CreateDefaultSubobject<URPGCharacterWidgetComponent>(TEXT("CharacterWidgetComponent"));
    WidgetComponent->SetupAttachment(RootComponent);
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void ARPGCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& data)
        {
            OnHealthAttributeChangedDelegate.Broadcast(data.OldValue, data.NewValue, RPGAttributeSet->GetMaxHealth());
        });
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAttributeSet->GetStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& data)
        {
            OnStaminaAttributeChangedDelegate.Broadcast(data.OldValue, data.NewValue, RPGAttributeSet->GetMaxStamina());
        });

        AbilitySystemComponent->InitAbilityActorInfo(this, this);

        InitializeAttributes();
        InitializeAbilities();
    }
}

void ARPGCharacter::BlockMovement(bool blocked)
{
    if (UCharacterMovementComponent* characterMovementComponent = GetCharacterMovement())
    {
        if (blocked)
        {
            characterMovementComponent->DisableMovement();
        }
        else
        {
            characterMovementComponent->SetDefaultMovementMode();
        }
    }
}

void ARPGCharacter::BeginHandleMeleeAttack()
{
    RPG_LOG(Log, TEXT("BeginHandleMeleeAttack"));
    MeleeAttackBoxComponent->SetGenerateOverlapEvents(true);
}

void ARPGCharacter::EndHandleMeleeAttack()
{
    RPG_LOG(Log, TEXT("EndHandleMeleeAttack"));
    MeleeAttackBoxComponent->SetGenerateOverlapEvents(false);
}

void ARPGCharacter::OnMeleeAttackBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        OnHitMeleeAttackDelegate.Broadcast(OtherActor);
    }
}

void ARPGCharacter::InitializeAttributes()
{
    if (AbilitySystemComponent)
    {
        FGameplayEffectContextHandle effectContext = AbilitySystemComponent->MakeEffectContext();
        effectContext.AddSourceObject(this);

        for (const TSubclassOf<UGameplayEffect>& effectClass : StartupGameplayEffects)
        {
            FGameplayEffectSpecHandle specHandle = AbilitySystemComponent->MakeOutgoingSpec(effectClass, 1.f, effectContext);
            if (specHandle.IsValid())
            {
                AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
            }
        }
    }
}

void ARPGCharacter::InitializeAbilities()
{
    if (AbilitySystemComponent)
    {
        for (const TSubclassOf<URPGGameplayAbility>& abilityClass : Abilities)
        {
            const FGameplayAbilitySpec abilitySpec(abilityClass, 1, static_cast<int32>(abilityClass.GetDefaultObject()->AbilityInput), this);
            AbilitySystemComponent->GiveAbility(abilitySpec);
        }
    }
}
