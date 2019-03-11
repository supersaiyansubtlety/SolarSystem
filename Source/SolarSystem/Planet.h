// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Planet.generated.h"

UCLASS()
class SOLARSYSTEM_API APlanet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanet();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    

    URotatingMovementComponent* SunOrbiter;
    URotatingMovementComponent* SelfOrbiter;
    UStaticMeshComponent* visualSphere;

    
    void ConstructAndBegin();
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
//    UPROPERTY(EditAnywhere, Category = "-Planet")
//    URotatingMovementComponent* RotatingComponent;
    
//    UPROPERTY(EditAnywhere, Category = "-Planet")
    USphereComponent* collisionSphere;
//    UPROPERTY(EditAnywhere, Category = "-Planet")
//    UStaticMeshComponent* visualSphere;
    
    UPROPERTY(EditAnywhere, Category = "-Planet")
    UMaterialInterface* material;
    
    UPROPERTY(EditAnywhere, Category = "-Planet")
    float startY_Offset;
    UPROPERTY(EditAnywhere, Category = "-Planet")
    float scale;
    
    UPROPERTY(EditAnywhere, Category = "-Planet")
    float sunOrbitRate;
    UPROPERTY(EditAnywhere, Category = "-Planet")
    float selfOrbitRate;
    
    

};
