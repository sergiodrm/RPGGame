#include "RPGCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPG/AbilitySystem/RPGAttributeSet.h"

ARPGCharacter::ARPGCharacter()
{
    bUseControllerRotationYaw = false;

    UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
    capsuleComponent->SetCapsuleHalfHeight(96.f);
    capsuleComponent->SetCapsuleRadius(42.f);

    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    SkeletalMeshComponent->SetupAttachment(RootComponent);
    SkeletalMeshComponent->SetRelativeLocation({0.f, 0.f, -capsuleComponent->GetScaledCapsuleHalfHeight()});
    SkeletalMeshComponent->SetRelativeRotation({0.f, -90.f, 0.f});

    SwordMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordMeshComponent"));
    SwordMeshComponent->SetupAttachment(SkeletalMeshComponent, TEXT("RightHandSocket"));

    ShieldStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMeshComponent"));
    ShieldStaticMeshComponent->SetupAttachment(SkeletalMeshComponent, TEXT("ShieldSocket"));

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(SkeletalMeshComponent);
    SpringArmComponent->TargetArmLength = 200.f;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
    AbilitySystemComponent->SetIsReplicated(false);

    RPGAttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("RGPAttributeSet"));
}

void ARPGCharacter::BeginPlay()
{
    Super::BeginPlay();
    // Set input context
    if (APlayerController* controller = GetController<APlayerController>())
    {
        // Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
        if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
        {
            // PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
            subsystem->ClearAllMappings();

            // Add each mapping context, along with their priority values. Higher values outprioritize lower values.
            subsystem->AddMappingContext(InputMapping, 0);
        }
    }

    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAttributeSet->GetHealthAttribute()).AddLambda([](const FOnAttributeChangeData& data)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, FString::Printf(TEXT("Health changed: %f"), data.NewValue));
            }
        });

        if (Ability)
        {
            const FGameplayAbilitySpec abilitySpec(Ability, 1, static_cast<uint8>(ERPGAbilityInput::Ability1));
            AbilitySystemComponent->GiveAbility(abilitySpec);
            AbilitySystemComponent->InitAbilityActorInfo(this, this);
        }
    }
}

void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ARPGCharacter::OnStartJump);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ARPGCharacter::OnEndJump);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ARPGCharacter::OnMoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ARPGCharacter::OnMoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ARPGCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ARPGCharacter::LookUp);


    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent,
                                                                      FGameplayAbilityInputBinds(
                                                                                                 TEXT("ConfirmTarget"),
                                                                                                 TEXT("CancelTarget"),
                                                                                                 TEXT("ERPGAbilityInput"),
                                                                                                 static_cast<int32>(ERPGAbilityInput::Confirm),
                                                                                                 static_cast<int32>(ERPGAbilityInput::Cancel)
                                                                                                ));
    }
}

bool ARPGCharacter::IsJumping() const
{
    return GetCharacterMovement()->MovementMode == MOVE_Falling;
}


void ARPGCharacter::OnStartJump()
{
    Jump();
}

void ARPGCharacter::OnEndJump()
{
    StopJumping();
}

void ARPGCharacter::OnMoveForward(float value)
{
    const FVector direction {value, 0.f, 0.f};
    const FRotator forward = GetControlRotation();
    AddMovementInput(forward.RotateVector(direction));
}

void ARPGCharacter::OnMoveRight(float value)
{
    const FVector direction {0.f, value, 0.f};
    const FRotator forward = GetControlRotation();
    AddMovementInput(forward.RotateVector(direction));
}

void ARPGCharacter::LookUp(float value)
{
    AddControllerPitchInput(value);
}

void ARPGCharacter::Turn(float value)
{
    AddControllerYawInput(value);
}
