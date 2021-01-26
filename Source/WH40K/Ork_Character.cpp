// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character.h"

// Sets default values
AOrk_Character::AOrk_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOrk_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOrk_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOrk_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

