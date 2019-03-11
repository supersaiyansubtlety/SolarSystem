// Fill out your copyright notice in the Description page of Project Settings.

#include "Planet.h"

// Sets default values
APlanet::APlanet():
startY_Offset(0),
scale(1),
sunOrbitRate(0),
selfOrbitRate(0)
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
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Shapes/Shape_Sphere.Shape_Sphere"));
    if (SphereVisualAsset.Succeeded())
    {
        visualSphere->SetStaticMesh(SphereVisualAsset.Object);
    }
    
    visualSphere->SetMobility(EComponentMobility::Movable);

    SelfOrbiter = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("SelfOrbiter"));//this);//,
    SelfOrbiter->SetUpdatedComponent(visualSphere);
    
    SunOrbiter = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("SunOrbiter"));//this);//,
    SunOrbiter->SetUpdatedComponent(GetRootComponent());
    
    ConstructAndBegin();
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
    ConstructAndBegin();

}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlanet::ConstructAndBegin()
{
    if (material)
    {
        visualSphere->SetMaterial(0, material);
    }
    
    SetActorLocation(FVector(0, startY_Offset, 0));
    collisionSphere->SetWorldScale3D(FVector(scale));
    collisionSphere->SetCollisionProfileName(TEXT("Planet"));
    
    visualSphere->SetWorldScale3D(FVector((scale * 32 / 50)));
    visualSphere->SetRelativeLocation(FVector(0, 0, -scale * 32));
    
    SelfOrbiter->RotationRate = FRotator(0, selfOrbitRate, 0);
    SunOrbiter->PivotTranslation = FVector(0, -startY_Offset, 0);
    SunOrbiter->RotationRate = FRotator(0, sunOrbitRate, 0);

	name = "Some name";
}

