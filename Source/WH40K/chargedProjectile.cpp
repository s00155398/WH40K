// Fill out your copyright notice in the Description page of Project Settings.


#include "chargedProjectile.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include <WH40K/Ork_Character.h>

// Sets default values
AchargedProjectile::AchargedProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	MovementComponent->SetUpdatedComponent(Sphere);
	MovementComponent->InitialSpeed = 6000.0f;
	MovementComponent->MaxSpeed = 10000.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bShouldBounce = true;
	MovementComponent->Bounciness = 0.3f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>("Sphere");
	RootComponent = Sphere;
	
	RadialForce = CreateDefaultSubobject<URadialForceComponent>("Radial Force");
	RadialForce->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);
	
	ConstructorHelpers::FObjectFinder<USoundCue> Explosion(TEXT("SoundCue'/Game/Audio/Explosion02_Cue.Explosion02_Cue'"));
	if (Explosion.Object) {
		ExplosionCue = Explosion.Object;
	}

	Audio = CreateDefaultSubobject<UAudioComponent>("Audio");
	Audio->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);
	Audio->SetSound(ExplosionCue);
	Audio->bAutoActivate = false;

	ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("ParticleSystem'/Game/FireCaste/Projectile/P_CarbinePrimary_Trail.P_CarbinePrimary_Trail'"));
	if (Particle.Object) {
		ParticleTemplate = Particle.Object;
	}
	

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("Particle System");
	ParticleSystem->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystem->SetTemplate(ParticleTemplate);

	ConstructorHelpers::FObjectFinder<UParticleSystem> ChargedShotHit(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_waterBallHit.P_ky_waterBallHit'"));
	if (ChargedShotHit.Object) {
		ChargedParticleTemplate = ChargedShotHit.Object;
	}


	ChargedParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("Charged Particle System");
	ChargedParticleSystem->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);
	ChargedParticleSystem->SetTemplate(ChargedParticleTemplate);
	ChargedParticleSystem->bAutoActivate = false;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision Component");
	Collision->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);
	Collision->OnComponentBeginOverlap.AddDynamic(this,&AchargedProjectile::OnBeginOverlap);
	//setting a collision profile; each profile has default behaviors defined per channel
	Collision->SetCollisionProfileName("Projectile", true);

	//setting collision response type
	Collision->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);


	//this first line strips any preset collision responses and sets the component to ignore all
	Collision->BodyInstance.SetResponseToAllChannels(ECR_Ignore);

	//you can set individual response types for the channels you want; ECR_Overlap, ECR_Block, or ECR_Ignore
	//in this case all are set to trigger overlaps
	Collision->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Collision->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Collision->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Overlap);
	Collision->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	Collision->BodyInstance.SetResponseToChannel(ECC_Vehicle, ECR_Overlap);
	Collision->BodyInstance.SetResponseToChannel(ECC_Destructible, ECR_Overlap);
}

// Called when the game starts or when spawned
void AchargedProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AchargedProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AchargedProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag("Enemy") || OtherComp)
	{
		if (IsCharged == true)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, Audio->Sound, GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(this, ChargedParticleTemplate, GetActorLocation(), FRotator(0,0,0), FVector(carbineHeat/20));
			damage = carbineHeat * 1.5;
		}
		else
		{
			damage = 10;
		}
		AOrk_Character* ork = Cast<AOrk_Character>(OtherActor);

		if (ork && ork->Health > 0) {
			ork->projectileHit(ork, damage);
		}
		Destroy();
	}
}
