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


// Is the bird falling?
 bool ABird::IsFalling() const
{
	return (Bird->GetComponentVelocity().Z < 0.0f) & (bIsGrounded != true);
}