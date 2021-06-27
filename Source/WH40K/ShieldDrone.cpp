// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldDrone.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine\Classes\Components\AudioComponent.h"
#include "Sound/SoundCue.h"
// Sets default values
AShieldDrone::AShieldDrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Movement");
	FloatingMovement->SetUpdatedComponent(Sphere);

	SpawnFlare = CreateDefaultSubobject<UParticleSystemComponent>("Spawn Flare");
	SpawnFlare->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);

	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	DroneMesh->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	ShieldEffect = CreateDefaultSubobject<UParticleSystemComponent>("Shield Effect");
	ShieldEffect->AttachToComponent(DroneMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ShieldCollision = CreateDefaultSubobject<USphereComponent>("Shield Collision");
	ShieldCollision->AttachToComponent(DroneMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ShieldAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Shield Audio Component"));
	ShieldAudioComponent->bAutoActivate = false;

	ShieldAudioComponent->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AShieldDrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShieldDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShieldDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

