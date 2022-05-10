// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet\KismetMathLibrary.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"

#include "EBirdColor.h"

#include "Bird.generated.h"

UCLASS()
class FLAPPYBIRD_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void ApplyFlapForce();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsFalling() const;

	UFUNCTION(BlueprintCallable)
	void PauseFlapAnimation();

	UFUNCTION(BlueprintCallable)
	void Rotate(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SetAutoFlightLocation(float FlightAlpha);

	UFUNCTION(BlueprintCallable)
	void SetRandomBirdColor();

	UFUNCTION(BlueprintCallable)
	void UnpauseFlapAnimation();


protected:
	// config
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bird|Config")
	float AutoFlightMaximumElevation = 6.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|Config")
	float AutoFlightMinimumElevation = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|Config")
	FVector AutoFlightOrigin = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|Config")
	EBirdColor BirdColor = EBirdColor::Red;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|Config")
	FVector FlapImpulse = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|Config")
	FVector GetReadyOrigin = FVector(-55.0f, 0.0f, -60.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|Config")
	FVector MainMenuOrigin = FVector(0.0f, 0.0f, -35.0f);

	// state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|State")
	bool bHasDeathSFXPlayed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|State")
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|State")
	bool bIsFlapAnimationPaused = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bird|State")
	bool bIsGrounded = false;

	// components
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Bird|Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Bird|Components")
	UPaperFlipbookComponent* Bird;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Bird|Components")
	UCameraComponent* Camera;
};
