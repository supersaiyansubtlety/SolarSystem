// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SolarSystemGameMode.h"
#include "SolarSystemPawn.h"

ASolarSystemGameMode::ASolarSystemGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ASolarSystemPawn::StaticClass();
}
