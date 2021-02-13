// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character_ShootaBoy.h"
AOrk_Character_ShootaBoy::AOrk_Character_ShootaBoy()
{
	Shoota = CreateDefaultSubobject<UStaticMeshComponent>(FName("Shoota"));
	Shoota->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("Shoota_Socket"));

	MuzzleParticleSystem = CreateDefaultSubobject<UParticleSystem>(FName("Shoota Particle System"));

	IsAiming = false;
	IsFiring = false;

	ammo = 30;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ProjectileBlueprint(TEXT("Blueprint'/Game/ork/ShootaBoy/ShootaProjectile_BP.ShootaProjectile_BP'"));
	if (ProjectileBlueprint.Object) {
		MyProjectileBlueprint = (UClass*)ProjectileBlueprint.Object->GeneratedClass;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> anim(TEXT("AnimMontage'/Game/ork/ShootaBoy/Animations/Fire_Fast_Montage.Fire_Fast_Montage'"));

	FireMontage = anim.Object;

	ConstructorHelpers::FObjectFinder<USoundCue> Shot(TEXT("SoundCue'/Game/ork/ShootaBoy/Sound/Shoota_Wav_Cue.Shoota_Wav_Cue'"));

	ShootaShot = Shot.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimOne(TEXT("AnimMontage'/Game/ork/ShootaBoy/Animations/HitReact_Back_Montage.HitReact_Back_Montage'"));
	HitMontageOne = HitAnimOne.Object;

	bCanFire = true;

	Health = 100;
	HitCount = 0;

	BulletSpread = 0.5f;
	
	RandomizeActorScale(this);
	

}

void AOrk_Character_ShootaBoy::BeginPlay()
{
	SpawnOrkMeshProps(GetMesh());
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
			//BulletSpread = UKismetMathLibrary::RandomFloatInRange(0.0f, 10.0f);
			FRotator  ProjectileSpawnRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSocketLoc, PlayerLoc);

			ProjectileSpawnRotation.Pitch += UKismetMathLibrary::RandomFloatInRange(-5.0f, 5.0f);
			ProjectileSpawnRotation.Yaw += UKismetMathLibrary::RandomFloatInRange(-10.0f, 10.0f);
			ProjectileSpawnRotation.Roll += UKismetMathLibrary::RandomFloatInRange(-5.0f, 5.0f);

			if (ammo > 0)
			{
				AActor* Projectile = World->SpawnActor<AActor>(MyProjectileBlueprint, ProjectileSocketLoc, ProjectileSpawnRotation);
				PlayAnimMontage(FireMontage, 1.0f);
				UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, ShootaShot, ProjectileSocketLoc, FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, nullptr, true);
				ammo--;
				UGameplayStatics::SpawnEmitterAttached(MuzzleParticleSystem,Shoota, FName("ProjectileSocket"));
				World->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &AOrk_Character_ShootaBoy::ResetFire, 0.1f, false);
			}
			else
			{
				World->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AOrk_Character_ShootaBoy::Reload, 2.0f, false);
			}
		}
	}
	
}

void AOrk_Character_ShootaBoy::HitByProjectile()
{
	if (Health > 0)
	{
		PlayAnimMontage(HitMontageOne, 1.0f);
		UpdateHealth();
	}
}

void AOrk_Character_ShootaBoy::UpdateHealth()
{
	Health -= Damage;
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
	ammo = 30;
	bCanFire = true;
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
}
