// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERPGAbilityInput : uint8
{
    None,
    ConfirmAbility,
    CancelAbility,
    Attack,
    HeavyAttack,
    Heal,
};
