// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGGameModeBase.h"

#include "Character/RPGCharacter.h"
#include "Character/RPGPlayerController.h"

ARPGGameModeBase::ARPGGameModeBase()
{
    DefaultPawnClass = ARPGCharacter::StaticClass();
    PlayerControllerClass = ARPGPlayerController::StaticClass();
}
