// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TPS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class WH40K_API ATPS_HUD : public AHUD
{
	GENERATED_BODY()
protected:
	

public:
	virtual void DrawHUD() override;
	
};
