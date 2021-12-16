// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGGameModeBase.h"

#include "EngineUtils.h"
#include "Character/RPGCharacter.h"
#include "Character/RPGPlayerController.h"
#include "UI/RPGHUD.h"

ARPGGameModeBase::ARPGGameModeBase()
{
    DefaultPawnClass = ARPGCharacter::StaticClass();
    PlayerControllerClass = ARPGPlayerController::StaticClass();
    HUDClass = ARPGHUD::StaticClass();
}

void ARPGGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}
