// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character_OrkBoy.h"
#include "GameFramework/Actor.h"
AOrk_Character_OrkBoy::AOrk_Character_OrkBoy()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponOne = CreateDefaultSubobject<UStaticMeshComponent>(FName("Weapon One"));
	WeaponTwo = CreateDefaultSubobject<UStaticMeshComponent>(FName("Weapon Two"));


	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimOne(TEXT("AnimMontage'/Game/ork/Animations/PrimaryAttack_LA_Montage.PrimaryAttack_LA_Montage'"));
	AttackMontageOne = AttackAnimOne.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimTwo(TEXT("AnimMontage'/Game/ork/Animations/PrimaryAttack_RA_Montage.PrimaryAttack_RA_Montage'"));
	AttackMontageTwo = AttackAnimTwo.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimThree(TEXT("AnimMontage'/Game/ork/OrkBoy/Animations/Melee_A_Montage.Melee_A_Montage'"));
	AttackMontageThree = AttackAnimThree.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimFour(TEXT("AnimMontage'/Game/ork/OrkBoy/Animations/Melee_C_Montage.Melee_C_Montage'"));
	AttackMontageFour = AttackAnimFour.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimOne(TEXT("AnimMontage'/Game/ork/Animations/HitReact_Front_Montage.HitReact_Front_Montage'"));
	HitMontageOne = HitAnimOne.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimTwo(TEXT("AnimMontage'/Game/ork/Animations/HitReact_Back_Montage.HitReact_Back_Montage'"));
	HitMontageTwo = HitAnimTwo.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimThree(TEXT("AnimMontage'/Game/ork/Animations/HitReact_Left_Montage.HitReact_Left_Montage'"));
	HitMontageThree = HitAnimThree.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimFour(TEXT("AnimMontage'/Game/ork/Animations/HitReact_Left_Montage.HitReact_Left_Montage'"));
	HitMontageFour = HitAnimFour.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> DeathAnim(TEXT("AnimMontage'/Game/ork/Animations/Death_A_Montage.Death_A_Montage'"));
	DeathMontage = DeathAnim.Object;

	SaveAttack = false;
	IsAttacking = true;
	AttackCount = 0;
	HitCount = 0;
	Health = 100;
	DeathCount = 0;
	DisintegrationChance = 0;
		
}

void AOrk_Character_OrkBoy::BeginPlay()
{
	Super::BeginPlay();
	WeaponOne->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Right_Weapon"));
	WeaponTwo->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Left_Weapon"));
	SpawnOrkProps(this);
	RandomizeActorScale(this);
}

void AOrk_Character_OrkBoy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsStunned)
	{
		GetCharacterMovement()->MaxWalkSpeed = 0;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}


void AOrk_Character_OrkBoy::AttackInitiated()
{
	if (IsAttacking && Health < 0)
	{
		SaveAttack = true;
	}
	else
	{
		IsAttacking = true;
		switch (AttackCount)
		{
		case 0:
			AttackCount = 1;
			PlayAnimMontage(AttackMontageOne, 1.0f);
			break;

		case 1:
			AttackCount = 0;
			PlayAnimMontage(AttackMontageThree, 1.0f);
			break;
		}
	}
}

void AOrk_Character_OrkBoy::ComboAttackSave()
{
	if (SaveAttack)
	{
		SaveAttack = false;
	}
	else
	{
		IsAttacking = true;
		switch (AttackCount)
		{
		case 0:
			AttackCount = 1;
			PlayAnimMontage(AttackMontageOne, 1.0f);
			break;

		case 1:
			AttackCount = 0;
			PlayAnimMontage(AttackMontageThree, 1.0f);
			break;
		}
	}
}

void AOrk_Character_OrkBoy::ResetCombo()
{
	if (AttackCount == 1)
	{
		AttackCount = 0;
	}
	else
	{
		AttackCount++;
	}
	SaveAttack = false;
	IsAttacking = false;
}

void AOrk_Character_OrkBoy::HitByProjectile(float dps)
{
	if (Health > 0)
	{
		HitCount = FMath::RandRange(0, 3);
		switch (HitCount)
		{
		case 0:
			PlayAnimMontage(HitMontageOne, 1.0f);
			break;
		case 1:
			PlayAnimMontage(HitMontageTwo, 1.0f);
			break;
		case 2:
			PlayAnimMontage(HitMontageThree, 1.0f);
			break;
		case 3:
			PlayAnimMontage(HitMontageFour, 1.0f);
			break;
		}
		UpdateHealth(dps);
	}
}

void AOrk_Character_OrkBoy::UpdateHealth(float dps)
{
		Health -= dps;
		if (dps > 11)
		{
			if (Health <= 0)
			{
				GetMesh()->bNoSkeletonUpdate = true;
				WeaponOne->DetachFromParent();
				WeaponOne->SetSimulatePhysics(true);

				WeaponTwo->DetachFromParent();
				WeaponTwo->SetSimulatePhysics(true);

				WeaponOne->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				WeaponTwo->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				WeaponOne->SetCollisionProfileName(FName("BlockAll"));
				WeaponTwo->SetCollisionProfileName(FName("BlockAll"));
				this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				this->GetController()->UnPossess();
				InitiateDisintegration();
			}
		}
		else
		{
			if (Health <= 0)
			{
				this->GetController()->UnPossess();
				WeaponOne->DetachFromParent();
				WeaponOne->SetSimulatePhysics(true);
				GetMesh()->SetSimulatePhysics(true);
				GetMesh()->SetCollisionProfileName("Ragdoll");
				WeaponTwo->DetachFromParent();
				WeaponTwo->SetSimulatePhysics(true);

				WeaponOne->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				WeaponTwo->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				WeaponOne->SetCollisionProfileName(FName("BlockAll"));
				WeaponTwo->SetCollisionProfileName(FName("BlockAll"));

				this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}

		}
}

void AOrk_Character_OrkBoy::projectileHit(AOrk_Character* OrkReference, float damageInflicted)
{
	Super::projectileHit(this, damageInflicted);
	Health -= damageInflicted;
	if (damageInflicted > 11)
	{
		if (Health <= 0)
		{
			WeaponOne->DetachFromParent();
			WeaponOne->SetSimulatePhysics(true);

			WeaponTwo->DetachFromParent();
			WeaponTwo->SetSimulatePhysics(true);

			WeaponOne->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			WeaponTwo->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			WeaponOne->SetCollisionProfileName(FName("BlockAll"));
			WeaponTwo->SetCollisionProfileName(FName("BlockAll"));
			this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetMesh()->SetSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			this->GetController()->UnPossess();
			InitiateDisintegration();
		}
	}
	else
	{
		if (Health <= 0)
		{
			this->GetController()->UnPossess();
			WeaponOne->DetachFromParent();
			WeaponOne->SetSimulatePhysics(true);
			GetMesh()->SetSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			WeaponTwo->DetachFromParent();
			WeaponTwo->SetSimulatePhysics(true);

			WeaponOne->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			WeaponTwo->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			WeaponOne->SetCollisionProfileName(FName("BlockAll"));
			WeaponTwo->SetCollisionProfileName(FName("BlockAll"));

			this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

	}
}