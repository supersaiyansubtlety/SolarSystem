// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnWithCamera.h"
//#include "MyActorToSpawn.h"


// Sets default values
APawnWithCamera::APawnWithCamera():
speed(300),
lerpAlpha(1),
numRevealed(0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    //Create our components
    //Create collision sphere and make it root
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(40.f);
    SphereComponent->SetCollisionProfileName(TEXT("Player"));
    
//    PawnMover = CreateDefaultSubobject<UMovementComponent>(TEXT("PawnMover"), true);
//    PawnMover->SetUpdatedComponent(GetRootComponent());
    
    OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
    OurCamera->SetupAttachment(GetRootComponent());
    
    //Take control of the default Player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    //Rotate our camera's pitch AND NOW YAW, but limit PITCH so we're always looking downward
    //NOTE: Camera's pitch is changing independent of actor's pitch
    if (lerpAlpha < 1)
    {
        //increment lerpAlpha so it reaches 1 after 5 seconds
        lerpAlpha += (DeltaTime/6);
        //get lerp and set rotation from lerp
        FRotator Lerped = FMath::Lerp(camForwardRot, newCamForwardRot, lerpAlpha);
        Lerped.Roll = 0;
        //GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, FString::Printf(TEXT("newRot: %f, %f, %f"), newRot.Pitch, newRot.Yaw, newRot.Roll));
        OurCamera->SetWorldRotation(Lerped);
        if (!(lerpAlpha < 1))
        {
            if (GetWorld())
            {
                APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
                if (myPlayerController)
                {
                    this->EnableInput(myPlayerController);
                    if (GEngine) { GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("Input enabled!"))); }
                }
            }
        }
    }
    else
    {
        if (GetWorld())
        {
            APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
            if (myPlayerController)
            {
                this->EnableInput(myPlayerController);
            }
        }
        
        {
            FRotator NewRotation = OurCamera->GetComponentRotation();
            NewRotation.Yaw = NewRotation.Yaw + CameraInput.X;
            NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, 80.0f);
            NewRotation.Roll = 0;
            OurCamera->SetWorldRotation(NewRotation);
        }
        
        //Handle movement based on our "MoveX" and "MoveY" axes
        {
            if (!MovementInput.IsZero())
            {
                //Scale our movement input axis values by 100 units per second
                MovementInput = MovementInput.GetSafeNormal() * speed;
                FVector NewLocation = GetActorLocation();
                FVector CameraForward = OurCamera->GetForwardVector();
                CameraForward = CameraForward.GetSafeNormal();
                NewLocation += CameraForward * MovementInput.X * DeltaTime;
                NewLocation += OurCamera->GetRightVector() * MovementInput.Y * DeltaTime;
                SetActorLocation(NewLocation);
            }
        }
    }
    //score messages
}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    
    //Hook up events for "ZoomIn"
    
    //Hook up every-frame handling for our four axes
    InputComponent->BindAxis("ForwardandBack", this, &APawnWithCamera::MoveBackward);
    InputComponent->BindAxis("LeftandRight", this, &APawnWithCamera::MoveRight);
    InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
    InputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);
    InputComponent->BindAction("Bearing", IE_Pressed, this, &APawnWithCamera::Bearing);
    InputComponent->BindAction("RevealActor", IE_Pressed, this, &APawnWithCamera::RevealActor);
}

//Input functions
void APawnWithCamera::MoveBackward(float AxisValue)
{
    MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
    MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue)
{
    CameraInput.Y = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
    CameraInput.X = AxisValue;
}

void APawnWithCamera::Bearing()
{
    if (lerpAlpha < 1) { return; }
    camForwardRot = OurCamera->GetForwardVector().Rotation();
    newCamForwardRot = (-GetActorLocation()).Rotation();
    
    lerpAlpha = 0;
  
    if (GetWorld())
    {
        APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
        if (myPlayerController)
        {
            this->DisableInput(myPlayerController);
            if (GEngine && !myPlayerController->InputEnabled())
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Input disabled!")));
            }
        }
    }
}

void APawnWithCamera::RevealActor()
{
    if (numRevealed < actorsToReveal.Num())
    {
        actorsToReveal[numRevealed]->SetActorHiddenInGame(false);
        numRevealed++;
    }
}
