// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClotGameMode.h"
#include "ClotCharacter.h"
#include "UObject/ConstructorHelpers.h"

AClotGameMode::AClotGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
