// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlyUpGameMode.h"
#include "FlyUpCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFlyUpGameMode::AFlyUpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
