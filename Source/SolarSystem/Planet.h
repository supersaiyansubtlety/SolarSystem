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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UPROPERTY(EditAnywhere, Category = "-Planet")
    URotatingMovementComponent* RotatingComponent;
    
    UPROPERTY(EditAnywhere, Category = "-Planet")
    USphereComponent* collisionSphere;
    UPROPERTY(EditAnywhere, Category = "-Planet")
    UStaticMeshComponent* visualSphere;
    
//    UPROPERTY(EditAnywhere, Category = "-Planet")
//    FString materialPath;
    
    UPROPERTY(EditAnywhere, Category = "-Planet")
    UMaterial* material;
//    UPROPERTY(EditAnywhere, Category = "-Planet")
//    UMaterialInstanceDynamic* materialInstance;
    
    UPROPERTY(EditAnywhere, Category = "-Planet")
    float startYOffset;
    UPROPERTY(EditAnywhere, Category = "-Planet")
    float scale;
    
//    UPROPERTY(EditAnywhere, Category = "-Planet")
//    float orbitDist;
    UPROPERTY(EditAnywhere, Category = "-Planet")
    float orbitRate;
    
    

};
