 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CarbineLaser.generated.h"

UCLASS()
class WH40K_API ACarbineLaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarbineLaser();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	UCapsuleComponent *Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent *Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UProjectileMovementComponent *MovementComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
