// Fill out your copyright notice in the Description page of Project Settings.

#include "Voyager.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"


// Sets default values
AVoyager::AVoyager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetupAttachment(RootComponent);
	//SphereComponent->SetCollisionEnabled();
	SphereComponent->SetCollisionProfileName(TEXT("Ship"));
	RootComponent = Camera;
	speed = 1000.0f;
	Alpha = 0.0f;
	Middle = FRotator(0, 0, 0);
	


}

// Called when the game starts or when spawned
void AVoyager::BeginPlay()
{
	Super::BeginPlay();
	move = false;
	finding = false;

	
}

// Called every frame
void AVoyager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	finding = false;
	if (finding == true) {

		if (GetWorld()) {
			APlayerController *myPlayerController = GetWorld()->GetFirstPlayerController();
			if (myPlayerController) {
				this->DisableInput(myPlayerController);
			}
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, FString::Printf(TEXT("Inputs Disabled")));
			}
		}

		Alpha += DeltaTime / 6;
		Alpha = FMath::Clamp<float>(Alpha, 0.0f, 1.0f);
		FRotator Lerped = FMath::Lerp(CameraRot, Middle, Alpha);
		Camera->SetWorldRotation(Lerped);

		if (Alpha == 1) {
			finding = false;
			Alpha = 0.0f;
			if (GetWorld()) {
				APlayerController *myPlayerController = GetWorld()->GetFirstPlayerController();
				if (myPlayerController) {
					this->EnableInput(myPlayerController);
				}
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, FString::Printf(TEXT("Inputs Enabled")));
				}
			}
		}
	}

	FRotator NewRotation = Camera->GetComponentRotation();
	NewRotation.Yaw += CameraInput.X;
	NewRotation.Pitch += CameraInput.Y;
	Camera->SetWorldRotation(NewRotation);

	if (move) {
		MovementInput = MovementInput.GetSafeNormal() * speed;
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(2, 7.0f, FColor::Red, FString::Printf(TEXT("Movement Input: %s"), *MovementInput.ToString()));
		}
		FVector NewLocation = GetActorLocation();
		NewLocation += Camera->GetForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += Camera->GetRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
		move = false;
	}




}

// Called to bind functionality to input
void AVoyager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//InputComponent->BindAxis("Right", this, &AVoyager::MoveRight);
	InputComponent->BindAxis("LeftandRight", this, &AVoyager::MoveLeft);
	InputComponent->BindAxis("ForwardandBack", this, &AVoyager::MoveBackward);
	//InputComponent->BindAxis("Backward", this, &AVoyager::MoveBackward);
	InputComponent->BindAxis("CameraPitch", this, &AVoyager::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &AVoyager::YawCamera);
	InputComponent->BindAxis("Bearing", this, &AVoyager::Bearing);


}

void AVoyager::Bearing(float AxisValue) {
	CameraRot = Camera->GetComponentRotation();
	finding = true;
	
}

void AVoyager::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void AVoyager::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}


void AVoyager::MoveLeft(float AxisValue) {
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	move = true;
}

void AVoyager::MoveBackward(float AxisValue) {
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	move = true;
}
