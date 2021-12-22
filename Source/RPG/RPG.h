// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define RPG_LOG(Level, Format, ...) UE_LOG(LogRPG, Level, Format, __VA_ARGS__)

DECLARE_LOG_CATEGORY_EXTERN(LogRPG, Log, All);

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
