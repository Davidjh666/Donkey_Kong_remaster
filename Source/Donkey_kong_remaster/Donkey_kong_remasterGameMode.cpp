// Copyright Epic Games, Inc. All Rights Reserved.

#include "Donkey_kong_remasterGameMode.h"
#include "Donkey_kong_remasterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADonkey_kong_remasterGameMode::ADonkey_kong_remasterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
