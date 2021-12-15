// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGGameModeBase.h"

#include "EngineUtils.h"
#include "Character/RPGCharacter.h"
#include "Character/RPGPlayerController.h"
#include "GameFramework/PlayerStart.h"

ARPGGameModeBase::ARPGGameModeBase()
{
    DefaultPawnClass = ARPGCharacter::StaticClass();
    PlayerControllerClass = ARPGPlayerController::StaticClass();
}

void ARPGGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}
