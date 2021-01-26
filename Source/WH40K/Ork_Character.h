// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FireWarrior_Character.h"
#include "Ork_Character.generated.h"


UCLASS()
class WH40K_API AOrk_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOrk_Character();

	AFireWarrior_Character* FireWarriorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* AttackMontageOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* AttackMontageTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* HitMontageOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* HitMontageTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* HitMontageThree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* HitMontageFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool SaveAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int AttackCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int HitCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int DeathCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int DisintegrationChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	

	
};
