// Fill out your copyright notice in the Description page of Project Settings.

#include "Planet.h"

// Sets default values
APlanet::APlanet():
//materialPath(""),
startPos(0),
scale(1),
//orbitDist(0),
orbitRate(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    
    collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("collisionSphere"));
    collisionSphere->SetupAttachment(RootComponent);
//    collisionSphere->SetSimulatePhysics(true);
//    collisionSphere->SetEnableGravity(false);
    
    visualSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    visualSphere->SetupAttachment(RootComponent);
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (SphereVisualAsset.Succeeded())
    {
        visualSphere->SetStaticMesh(SphereVisualAsset.Object);
    }
    
    // Setup mobility
    visualSphere->SetMobility(EComponentMobility::Movable);

    // Create movement component and set rotation rate
    RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));//this);//,
    RotatingComponent->SetUpdatedComponent(GetRootComponent());
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
    SetActorLocation(startPos);
    collisionSphere->SetWorldScale3D(FVector(scale));
    collisionSphere->SetCollisionProfileName(TEXT("Planet"));
    
    visualSphere->SetWorldScale3D(FVector((scale * 32 / 50)));
    visualSphere->SetRelativeLocation(FVector(0, 0, -scale * 32 / 50));
    
    
    RotatingComponent->RotationRate = FRotator(0, 0, orbitRate);
    RotatingComponent->PivotTranslation = FVector(startPos.Y, 0, 0);

//    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
//    if (SphereVisualAsset.Succeeded())
//    {
//        visualSphere->SetStaticMesh(SphereVisualAsset.Object);
//        visualSphere->SetWorldScale3D(FVector(scale/2));
//    }
    
//    static ConstructorHelpers::FObjectFinder<UMaterial> material(TEXT("/Game/StarterContent/Materials/M_Ground_Moss.M_Ground_Moss"));
//    if (material.Succeeded())
//    {
//        visualSphere->SetMaterial(0, material.Object);
//    }
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (GEngine)
    {
//        GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Blue, FString::Printf(TEXT("Visual radius: %f"), visualSphere->CalcBounds(FTransform()).SphereRadius));
//        GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Blue, FString::Printf(TEXT("Visual extent: %f, %f, %f"),
//                                                                               visualSphere->CalcBounds(FTransform()).BoxExtent.X,
//                                                                               visualSphere->CalcBounds(FTransform()).BoxExtent.Y,
//                                                                               visualSphere->CalcBounds(FTransform()).BoxExtent.Z));
//        GEngine->AddOnScreenDebugMessage(7, 1.f, FColor::Blue, FString::Printf(TEXT("Collision radius: %f"), collisionSphere->CalcBounds(FTransform()).SphereRadius));
//        GEngine->AddOnScreenDebugMessage(8, 1.f, FColor::Blue, FString::Printf(TEXT("Collision extent: %f, %f, %f"),
//                                                                               collisionSphere->CalcBounds(FTransform()).BoxExtent.X,
//                                                                               collisionSphere->CalcBounds(FTransform()).BoxExtent.Y,
//                                                                               collisionSphere->CalcBounds(FTransform()).BoxExtent.Z));
    }
}

