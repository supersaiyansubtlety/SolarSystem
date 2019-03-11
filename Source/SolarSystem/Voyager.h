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
	float A2;
	

	bool finding;
	bool move;
	bool moving;
	bool bearing;
	

	UCameraComponent* Camera;

	FVector2D MovementInput;
	FVector2D CameraInput;
	FVector CameraLoc;
	FRotator Middle;
	FRotator CameraRot;
	FVector distFS;
	FRotator look;

	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);


	void Bearing(float AxixValue);
	void MoveLeft(float AxisValue);
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
