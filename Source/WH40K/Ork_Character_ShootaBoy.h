// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ork_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include <FMODBlueprintStatics.h>
#include "Ork_Character_ShootaBoy.generated.h"

/**
 * 
 */
UCLASS()
class WH40K_API AOrk_Character_ShootaBoy : public AOrk_Character
{
	GENERATED_BODY()
	
protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:


	AOrk_Character_ShootaBoy();

	UPROPERTY(EditAnywhere, Category = "FMOD")
		class UFMODEvent* Event;

	FFMODEventInstance InstanceWrapper;

	UPROPERTY(EditAnywhere, Category = "FMOD")
		class UFMODAudioComponent* AudioComponent;

	bool IsAudioPlaying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UStaticMeshComponent* Shoota;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool IsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool IsFiring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool IsReloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Opponent")
		AActor* Opponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int fullAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread;

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
	UFUNCTION(BlueprintCallable)
		void HitByProjectile();
	UFUNCTION()
		void UpdateHealth();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void InitiateDisintegration();
	UFUNCTION()
		void StartFireAudio();
	UFUNCTION()
		void StopFireAudio();
};
