// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime/Engine/Classes/Components/CapsuleComponent.h>
#include <Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h>
#include "Sound/SoundCue.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "chargedProjectile.generated.h"

UCLASS()
class WH40K_API AchargedProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AchargedProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		URadialForceComponent* RadialForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Sphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* Audio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* ParticleSystem;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* Collision;
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float carbineHeat = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage = 0;

	UParticleSystem* ParticleTemplate;
	USoundCue* ExplosionCue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
