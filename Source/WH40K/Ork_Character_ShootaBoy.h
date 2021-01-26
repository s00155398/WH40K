// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ork_Character.h"
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


	

};
