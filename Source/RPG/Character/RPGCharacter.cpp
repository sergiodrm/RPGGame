#include "RPGCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

    ShieldMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShieldMeshComponent"));
    ShieldMeshComponent->SetupAttachment(SkeletalMeshComponent);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(SkeletalMeshComponent);
    SpringArmComponent->TargetArmLength = 200.f;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
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
}

void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (inputComponent)
    {
        if (InputActions.MovementAction)
        {
            inputComponent->BindAction(InputActions.MovementAction, ETriggerEvent::Triggered, this, &ARPGCharacter::OnMovementAction);
        }
        if (InputActions.JumpAction)
        {
            inputComponent->BindAction(InputActions.JumpAction, ETriggerEvent::Started, this, &ARPGCharacter::OnStartJumpAction);
            inputComponent->BindAction(InputActions.JumpAction, ETriggerEvent::Completed, this, &ARPGCharacter::OnEndJumpAction);
        }
        if (InputActions.LookAction)
        {
            inputComponent->BindAction(InputActions.LookAction, ETriggerEvent::Triggered, this, &ARPGCharacter::OnLookAction);
        }
    }
}

bool ARPGCharacter::IsJumping() const
{
    return GetCharacterMovement()->MovementMode == MOVE_Falling;
}

void ARPGCharacter::OnMovementAction(const FInputActionValue& actionValue)
{
    ensure(actionValue.GetValueType() == EInputActionValueType::Axis2D);
    const FVector direction {actionValue[0], actionValue[1], 0.f};
    const FRotator forward = GetControlRotation();
    AddMovementInput(forward.RotateVector(direction));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Red, FString::Printf(TEXT("OnMovementAction: %s"), *actionValue.ToString()));
    }
}

void ARPGCharacter::OnStartJumpAction(const FInputActionValue& actionValue)
{
    Jump();
}

void ARPGCharacter::OnEndJumpAction(const FInputActionValue& actionValue)
{
    StopJumping();
}

void ARPGCharacter::OnLookAction(const FInputActionValue& actionValue)
{
    ensure(actionValue.GetValueType() == EInputActionValueType::Axis2D);
    AddControllerPitchInput(-actionValue[1]);
    AddControllerYawInput(actionValue[0]);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Red, FString::Printf(TEXT("OnLookAction: %s"), *actionValue.ToString()));
    }
}
