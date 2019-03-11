// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Engine.h"
#include "Components/SphereComponent.h"
#include "PawnWithCamera.generated.h"

UCLASS()
class SOLARSYSTEM_API APawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnWithCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	UFUNCTION()
	void OnOverlap(AActor* Overlapped, AActor* OtherThis);
    
protected:
    UCameraComponent* OurCamera;
    
    //Input variables to store the data we receive from input mappings
    FVector2D MovementInput;
    FVector2D CameraInput;
    UPROPERTY(EditAnywhere, Category = "-Movement")
    float speed;
	UPROPERTY(EditAnywhere, Category = "BearingSpeed")
	float BearS;
    //lerp stuff
    float lerpAlpha;
	float A2;
	float TimeToFB;
	bool move;
	bool finding;
    
	FVector startdist;
	FVector enddist;
    FVector spawnLoc;
    FVector spawnOffset;
    FRotator camForwardRot;
    FRotator newCamForwardRot;

    UPROPERTY(EditAnywhere, Category = "-Solar Specific")
    TArray<AActor*> actorsToReveal;
    int32 numRevealed;
    void RevealActor();
    
    //Input functions
    void MoveBackward(float AxisValue);
    void MoveRight(float AxisValue);
    void PitchCamera(float AxisValue);
    void YawCamera(float AxisValue);
    void Bearing();

	
	
};
