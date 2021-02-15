// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character_OrkBoy.h"
#include "GameFramework/Actor.h"
AOrk_Character_OrkBoy::AOrk_Character_OrkBoy()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponOne = CreateDefaultSubobject<UStaticMeshComponent>(FName("Weapon One"));
	WeaponTwo = CreateDefaultSubobject<UStaticMeshComponent>(FName("Weapon Two"));

	WeaponOne->OnComponentBeginOverlap.AddDynamic(this, &AOrk_Character_OrkBoy::OnBeginOverlap);
	WeaponTwo->OnComponentBeginOverlap.AddDynamic(this, &AOrk_Character_OrkBoy::OnBeginOverlap);

	

	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimOne(TEXT("AnimMontage'/Game/ork/Animations/PrimaryAttack_LA_Montage.PrimaryAttack_LA_Montage'"));
	AttackMontageOne = AttackAnimOne.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimTwo(TEXT("AnimMontage'/Game/ork/Animations/PrimaryAttack_RA_Montage.PrimaryAttack_RA_Montage'"));
	AttackMontageTwo = AttackAnimTwo.Object;

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
	Damage = 10;

	
	RandomizeActorScale(this);
	
	
}

void AOrk_Character_OrkBoy::BeginPlay()
{
	Super::BeginPlay();
	WeaponOne->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Right_Weapon"));
	WeaponTwo->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Left_Weapon"));
	SpawnOrkMeshProps(GetMesh());
}

void AOrk_Character_OrkBoy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOrk_Character_OrkBoy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	if (OtherActor != NULL && OtherActor->ActorHasTag(TEXT("Player")))
	{
		if (IsAttacking)
		{
			AFireWarrior_Character* PlayerCharacter = Cast<AFireWarrior_Character>(OtherActor);
			PlayerCharacter->HitByEnemy();
			IsAttacking = false;
		}
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
			PlayAnimMontage(AttackMontageTwo, 1.0f);
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
			PlayAnimMontage(AttackMontageTwo, 1.0f);
			break;
		}
	}
}

void AOrk_Character_OrkBoy::ResetCombo()
{
	AttackCount = 0;
	SaveAttack = false;
	IsAttacking = false;
}

void AOrk_Character_OrkBoy::HitByProjectile()
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
		UpdateHealth();
	}
}

void AOrk_Character_OrkBoy::UpdateHealth()
{
	Health -= Damage;
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

		this->DetachFromControllerPendingDestroy();
		this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		InitiateDisintegration();
	}
}
