// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundCue.h"
#include "FireWarrior_Character.generated.h"

UCLASS()
class WH40K_API AFireWarrior_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFireWarrior_Character();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent*  CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* Carbine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UArrowComponent* AimingArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* MuzzleFlashParticleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BaseLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool SaveAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int AttackCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsAiming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsFiring;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float CoolDownSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	UCurveFloat *AimTimelineCurve;

	FTimeline AimTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	UCurveFloat* OverHeatTimelineCurve;

	FTimeline OverHeatAimTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbine")
	float CarbineHeat = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbine")
	bool IsOverHeating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage *FireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* ChargeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* HitMontageOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* HitMontageTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* HitMontageThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* HitMontageFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DodgeForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DodgeBackward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DodgeRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DodgeLeft;
	
	USoundCue* OverheatAudioCue;
	UAudioComponent* OverheatAudioComponent;

	USoundCue* ChargeAudioCue;
	UAudioComponent* ChargeAudioComponent;

	FVector StartLoc;

	FRotator StartRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbine")
	int FireMode;

	FTimerHandle FireTimerHandle;

	FTimerHandle ChargeTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FTimerHandle DodgeCooldownTimerHandle; 

	USoundCue* CarbineShot;
	USoundCue* chargedCarbineShot;
	UParticleSystem* MuzzleFlashParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int HitCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool canDodge = true;
	UPROPERTY()
	int dodgeCounter = 0;


	float tempCarbineHeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone")
		bool SpawningDrone;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input Functions
	UFUNCTION()
	void Aim();
	UFUNCTION()
	void Aimout();
	UFUNCTION()
	void Fire();
	UFUNCTION()
	void ChargeFire();
	UFUNCTION()
	void StopFire();
	UFUNCTION()
	void AimTimelineFunc(float BoomArmLength);
	UFUNCTION()
	void FireProjectile();
	UFUNCTION()
	void OverHeatTimelineFunc(float Duration);
	UFUNCTION()
	void ChangeFireMode();
	UFUNCTION()
	void CheckFire();
	UFUNCTION(BlueprintCallable)
	void HitByEnemy();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitiateCameraShake();
	UFUNCTION()
	void leftDodge();
	UFUNCTION()
	void rightDodge();
	UFUNCTION()
	void frontDodge();
	UFUNCTION()
	void backDodge();
	UFUNCTION()
	void ResetDodge();
};
