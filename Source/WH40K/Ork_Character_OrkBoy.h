// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ork_Character.h"
#include "Components/BoxComponent.h"
#include "Ork_Character_OrkBoy.generated.h"

UCLASS()
class WH40K_API AOrk_Character_OrkBoy : public AOrk_Character
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	

		AOrk_Character_OrkBoy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UStaticMeshComponent* WeaponOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UStaticMeshComponent* WeaponTwo;
	
	
	
	UFUNCTION(BlueprintCallable)
		void AttackInitiated();
	UFUNCTION(BlueprintCallable)
		void ComboAttackSave();
	UFUNCTION(BlueprintCallable) 
		void ResetCombo();

	UFUNCTION(BlueprintCallable)
		void HitByProjectile();
	UFUNCTION()
		void UpdateHealth();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void InitiateDisintegration();
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
