// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character_ShootaBoy.h"
AOrk_Character_ShootaBoy::AOrk_Character_ShootaBoy()
{
	Shoota = CreateDefaultSubobject<UStaticMeshComponent>(FName("Shoota"));
	Shoota->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("Shoota_Socket"));

	MuzzleParticleSystem = CreateDefaultSubobject<UParticleSystem>(FName("Shoota Particle System"));

	IsAiming = false;
	IsFiring = false;

	ammo = 5;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ProjectileBlueprint(TEXT("Blueprint'/Game/ork/ShootaBoy/ShootaProjectile_BP.ShootaProjectile_BP'"));
	if (ProjectileBlueprint.Object) {
		MyProjectileBlueprint = (UClass*)ProjectileBlueprint.Object->GeneratedClass;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> anim(TEXT("AnimMontage'/Game/ork/ShootaBoy/Animations/Fire_Fast_Montage.Fire_Fast_Montage'"));

	FireMontage = anim.Object;

	ConstructorHelpers::FObjectFinder<USoundCue> Shot(TEXT("SoundCue'/Game/ork/ShootaBoy/Sound/Shoota_Wav_Cue.Shoota_Wav_Cue'"));

	ShootaShot = Shot.Object;

	bCanFire = true;
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

			if (ammo > 0)
			{
				AActor* Projectile = World->SpawnActor<AActor>(MyProjectileBlueprint, ProjectileSocketLoc, ProjectileSpawnRotation);
				PlayAnimMontage(FireMontage, 1.0f);
				UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, ShootaShot, ProjectileSocketLoc, FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, nullptr, true);
				ammo--;
				UGameplayStatics::SpawnEmitterAttached(MuzzleParticleSystem,Shoota, FName("ProjectileSocket"));
				World->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &AOrk_Character_ShootaBoy::ResetFire, 0.2f, false);
			}
			else
			{
				World->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AOrk_Character_ShootaBoy::Reload, 2.0f, false);
			}
		}
	}
	
}

void AOrk_Character_ShootaBoy::ResetFire()
{
	bCanFire = true;
	GetWorldTimerManager().ClearTimer(FireDelayTimerHandle);
}

void AOrk_Character_ShootaBoy::Reload()
{
	ammo = 5;
	bCanFire = true;
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
}
