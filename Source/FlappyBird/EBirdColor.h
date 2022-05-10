#pragma once

#include "EBirdColor.generated.h"

UENUM(BlueprintType)
enum class EBirdColor : uint8
{
	Blue	UMETA(DisplayName = "Blue"),
	Red		UMETA(DisplayName = "Red"),
	Yellow	UMETA(DisplayName = "Yellow"),
	MAX		UMETA(Hidden)
};
