// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character_ShootaBoy.h"

AOrk_Character_ShootaBoy::AOrk_Character_ShootaBoy()
{
	GetMesh()->bNoSkeletonUpdate = false;
	Shoota = CreateDefaultSubobject<UStaticMeshComponent>(FName("Shoota"));
	Shoota->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("Shoota_Socket"));

	MuzzleParticleSystem = CreateDefaultSubobject<UParticleSystem>(FName("Shoota Particle System"));

	IsAiming = false;
	IsFiring = false;
	IsReloading = false;

	fullAmmo = 25;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ProjectileBlueprint(TEXT("Blueprint'/Game/ork/ShootaBoy/ShootaProjectile_BP.ShootaProjectile_BP'"));
	if (ProjectileBlueprint.Object) {
		MyProjectileBlueprint = (UClass*)ProjectileBlueprint.Object->GeneratedClass;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> anim(TEXT("AnimMontage'/Game/ork/ShootaBoy/Animations/Fire_A_Fast_V1_Montage.Fire_A_Fast_V1_Montage'"));
	if (anim.Object)
	{
		FireMontage = anim.Object;
	}
	

	ConstructorHelpers::FObjectFinder<USoundCue> Shot(TEXT("SoundCue'/Game/ork/ShootaBoy/Sound/Shoota_Wav_Cue.Shoota_Wav_Cue'"));
	if (Shot.Object) {
		ShootaShot = Shot.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimOne(TEXT("AnimMontage'/Game/ork/ShootaBoy/Animations/HitReact_Back_Montage.HitReact_Back_Montage'"));
	if (HitAnimOne.Object)
	{
		HitMontageOne = HitAnimOne.Object;
	}
	

	bCanFire = true;

	Health = 100;
	HitCount = 0;

	BulletSpread = 0.5f;
	
	ammo = fullAmmo;
	
}

void AOrk_Character_ShootaBoy::BeginPlay()
{
	Super::BeginPlay();
	RandomizeActorScale(this);
	SpawnOrkProps(this);
}

void AOrk_Character_ShootaBoy::Tick(float DeltaTime)
{
	PrimaryActorTick.bCanEverTick = true;

	Super::Tick(DeltaTime);
}

void AOrk_Character_ShootaBoy::FireShoota(ACharacter* PlayerRef)
{
		UWorld* const World = GetWorld();
		if (bCanFire)
		{
			bCanFire = false;

			if (PlayerRef != NULL && MuzzleParticleSystem != NULL)
			{
				FVector ProjectileSocketLoc = Shoota->GetSocketLocation(FName("ProjectileSocket"));
				FVector PlayerLoc = PlayerRef->GetActorLocation();
				FRotator  ProjectileSpawnRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSocketLoc, PlayerLoc);

				ProjectileSpawnRotation.Pitch += UKismetMathLibrary::RandomFloatInRange(-5.0f, 5.0f);
				ProjectileSpawnRotation.Yaw += UKismetMathLibrary::RandomFloatInRange(-10.0f, 10.0f);
				ProjectileSpawnRotation.Roll += UKismetMathLibrary::RandomFloatInRange(-5.0f, 5.0f);

				if (ammo > 0 && IsAiming)
				{
					IsAudioPlaying = true;

					IsFiring = true;
					AActor* Projectile = World->SpawnActor<AActor>(MyProjectileBlueprint, ProjectileSocketLoc, ProjectileSpawnRotation);
					PlayAnimMontage(FireMontage, 1.0f);
					ammo--;
					UGameplayStatics::SpawnEmitterAttached(MuzzleParticleSystem, Shoota, FName("ProjectileSocket"));
					World->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &AOrk_Character_ShootaBoy::ResetFire, 0.1f, false);
				}
				else
				{
					IsAudioPlaying = false;
					IsFiring = false;
					IsAiming = false;
					IsReloading = true;
					World->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AOrk_Character_ShootaBoy::Reload, 2.0f, false);
				}
			}
		}
}

void AOrk_Character_ShootaBoy::HitByProjectile(float dps)
{
	if (Health > 0)
	{
		PlayAnimMontage(HitMontageOne, 1.0f);
		UpdateHealth(dps);
	}
}

void AOrk_Character_ShootaBoy::UpdateHealth(float dps)
{
	Health -= dps;
	if (Health <= 0)
	{
		GetMesh()->bNoSkeletonUpdate = true;
		this->DetachFromControllerPendingDestroy();
		this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Shoota->DetachFromParent();
		Shoota->SetSimulatePhysics(true);
		InitiateDisintegration();
	}
}

void AOrk_Character_ShootaBoy::ResetFire()
{
	bCanFire = true;
	GetWorldTimerManager().ClearTimer(FireDelayTimerHandle);
}

void AOrk_Character_ShootaBoy::Reload()
{
	ammo = fullAmmo;
	bCanFire = true;
	IsAiming = true;
	IsReloading = false;
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
}