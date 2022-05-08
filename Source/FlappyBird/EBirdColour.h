#pragma once

#include "EBirdColour.generated.h"

UENUM(BlueprintType)
enum class EBirdColour : uint8
{
	Blue	UMETA(DisplayName = "Blue"),
	Red		UMETA(DisplayName = "Red"),
	Yellow	UMETA(DisplayName = "Yellow")
};
