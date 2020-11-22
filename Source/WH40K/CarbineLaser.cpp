// Fill out your copyright notice in the Description page of Project Settings.


#include "CarbineLaser.h"

// Sets default values
ACarbineLaser::ACarbineLaser()
{	
	/*
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision Component"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);

	MovementComponent = CreateAbstractDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	
	UStaticMesh* LaserMesh = MeshAsset.Object;
	if (MeshAsset.Object) {
		Mesh->SetStaticMesh(LaserMesh);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Mesh not found"));
	}

	MovementComponent->InitialSpeed = 12000;
	MovementComponent->MaxSpeed = 15000;
	*/
}

// Called when the game starts or when spawned
void ACarbineLaser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarbineLaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

