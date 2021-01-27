// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ork_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Ork_Character_ShootaBoy.generated.h"

/**
 * 
 */
UCLASS()
class WH40K_API AOrk_Character_ShootaBoy : public AOrk_Character
{
	GENERATED_BODY()
	
public:

	AOrk_Character_ShootaBoy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UStaticMeshComponent* Shoota;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool IsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool IsFiring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Opponent")
		AActor* Opponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* FireMontage;

	TSubclassOf<class AActor> MyProjectileBlueprint;

	
	USoundCue* ShootaShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle System")
	UParticleSystem* MuzzleParticleSystem;

	FTimerHandle FireDelayTimerHandle;
	FTimerHandle ReloadTimerHandle;

	bool bCanFire;

	void ResetFire();

	void Reload();

	UFUNCTION(BlueprintCallable)
		void FireShoota(ACharacter* PlayerRef);
};
