#pragma once
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "Voyager.generated.h"

UCLASS()
class SOLARSYSTEM_API AVoyager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVoyager();

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "MovementSpeed")
		float speed;

	float Alpha;

	bool finding;
	bool move;
	bool bearing;

	UCameraComponent* Camera;

	FVector2D MovementInput;
	FVector2D CameraInput;
	//FVector NewLocation;
	FVector CameraLoc;
	FRotator Middle;
	FRotator CameraRot;

	void Bearing(float AxixValue);
	void MoveRight(float AxisValue);
	void MoveLeft(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveBackward(float AxisValue);
	void YawCamera(float AxisValue);
	void PitchCamera(float AxisValue);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
