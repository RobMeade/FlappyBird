// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"

// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Bird = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Bird"));
	Bird->SetupAttachment(Scene);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Scene);
}


// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
}

// Apply flap force to bird
void ABird::ApplyFlapForce()
{
	Bird->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f), false);
	Bird->AddImpulse(FlapImpulse, NAME_None, true);
}

// Get grounded location
float ABird::GetGroundedLocation(UPrimitiveComponent* Base) const
{
	float constexpr BeakPlant = 10.0f;

	return (Base->GetComponentLocation().Z + Base->Bounds.BoxExtent.Z + BeakPlant);
}

// Is the bird falling?
bool ABird::IsFalling() const
{
	return (Bird->GetComponentVelocity().Z < 0.0f) & (bIsGrounded != true);
}

// Pause flap animation
void ABird::PauseFlapAnimation()
{
	int32 const PlaybackPositionFrame = Bird->GetPlaybackPositionInFrames();

	if ((PlaybackPositionFrame == 0 || PlaybackPositionFrame == 2) && (!bIsFlapAnimationPaused))
	{
		Bird->SetPlayRate(0.0f);

		bIsFlapAnimationPaused = true;
	}
}

// Rotate the bird
void ABird::Rotate(float DeltaTime)
{
	float Pitch = 0.0f;

	if (bIsGrounded)
	{
		Pitch = -90.0f;
	}
	else
	{
		Pitch = FMath::GetMappedRangeValueClamped(FVector2D(100.0f, -450.0f), FVector2D(20.0f, -90.0f), Bird->GetComponentVelocity().Z);
	}

	if ((Pitch == 0.0f) || (Pitch < 0.0f))
	{
		Pitch = FMath::FInterpTo(Bird->GetComponentRotation().Pitch, Pitch, DeltaTime, 10.0f);
	}

	Bird->SetWorldRotation(FRotator(Pitch, 0.0f, 0.0f));
}

// Set auto flight location
void ABird::SetAutoFlightLocation(float FlightAlpha)
{
	float const MaximumElevation = AutoFlightOrigin.Z + AutoFlightMinimumElevation + AutoFlightMaximumElevation;
	float const MinimumElevation = AutoFlightOrigin.Z + AutoFlightMinimumElevation;

	float const Elevation = FMath::Lerp(MaximumElevation, MinimumElevation, FlightAlpha);

	FVector const AutoFlightLocation = FVector(AutoFlightOrigin.X, AutoFlightOrigin.Y, Elevation);

	Bird->SetWorldLocation(AutoFlightLocation);
}

// Set random bird color
void ABird::SetRandomBirdColor()
{
	int32 const Index = FMath::RandRange(0, static_cast<uint8>(EBirdColor::MAX) - 1);

	BirdColor = static_cast<EBirdColor>(StaticEnum<EBirdColor>()->GetValueByIndex(Index));
}

// Unpause flap animation
void ABird::UnpauseFlapAnimation()
{
	if (bIsFlapAnimationPaused)
	{
		Bird->SetPlayRate(1.0f);
		bIsFlapAnimationPaused = false;
	}
}
