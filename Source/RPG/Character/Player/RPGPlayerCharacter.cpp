#include "RPGPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPG/RPG.h"

ARPGPlayerCharacter::ARPGPlayerCharacter()
{
    if (USkeletalMeshComponent* mesh = GetMesh())
    {
        SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
        SpringArmComponent->SetupAttachment(mesh);
        SpringArmComponent->TargetArmLength = 200.f;
        SpringArmComponent->bEnableCameraLag = true;
        SpringArmComponent->bUsePawnControlRotation = true;

        CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
        CameraComponent->SetupAttachment(SpringArmComponent);
    }
}

void ARPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ARPGPlayerCharacter::OnStartJump);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ARPGPlayerCharacter::OnEndJump);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ARPGPlayerCharacter::OnMoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ARPGPlayerCharacter::OnMoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ARPGPlayerCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ARPGPlayerCharacter::LookUp);


    if (AbilitySystemComponent)
    {
        const FGameplayAbilityInputBinds inputBinds(
                                                    TEXT("ConfirmTarget"),
                                                    TEXT("CancelTarget"),
                                                    TEXT("ERPGAbilityInput"),
                                                    static_cast<int32>(ERPGAbilityInput::ConfirmAbility),
                                                    static_cast<int32>(ERPGAbilityInput::CancelAbility)
                                                   );
        AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, inputBinds);
    }
}

void ARPGPlayerCharacter::OnStartJump()
{
    Jump();
}

void ARPGPlayerCharacter::OnEndJump()
{
    StopJumping();
}

void ARPGPlayerCharacter::OnMoveForward(float value)
{
    const FVector direction {value, 0.f, 0.f};
    const FRotator forward = GetControlRotation();
    AddMovementInput(forward.RotateVector(direction));
}

void ARPGPlayerCharacter::OnMoveRight(float value)
{
    const FVector direction {0.f, value, 0.f};
    const FRotator forward = GetControlRotation();
    AddMovementInput(forward.RotateVector(direction));
}

void ARPGPlayerCharacter::LookUp(float value)
{
    AddControllerPitchInput(value);
}

void ARPGPlayerCharacter::Turn(float value)
{
    AddControllerYawInput(value);
}
