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
#include "CarbineLaser.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbine")
		ACarbineLaser* Laser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage *FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* HitMontageOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* HitMontageTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* HitMontageThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* HitMontageFour;
	
	USoundCue* OverheatAudioCue;
	UAudioComponent* OverheatAudioComponent;

	FVector StartLoc;

	FRotator StartRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbine")
		int FireMode;

	FTimerHandle FireTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int HitCount;

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
	void StopFire();
	UFUNCTION(BlueprintCallable)
	void ResetCombo();
	UFUNCTION(BlueprintCallable)
	void ComboAttackSave();
	UFUNCTION()
	void AimTimelineFunc(float BoomArmLength);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FireProjectile();
	UFUNCTION()
	void OverHeatTimelineFunc(float Duration);
	UFUNCTION()
	void ChangeFireMode();
	UFUNCTION()
	void CheckFire();
	UFUNCTION()
	void HitByChoppa();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitiateCameraShake();
};
