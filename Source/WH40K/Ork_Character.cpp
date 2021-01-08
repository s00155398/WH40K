// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character.h"

// Sets default values
AOrk_Character::AOrk_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right Weapon"));
	RightWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("weapon_socket"));
	LeftWeapon = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Weapon"));
	LeftWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("Left_Weapon"));


	RightWeapon->OnComponentBeginOverlap.AddDynamic(this, &AOrk_Character::OnBeginOverlap);
	LeftWeapon->OnComponentBeginOverlap.AddDynamic(this, &AOrk_Character::OnBeginOverlap);

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
	IsAttacking = false;
	AttackCount = 0;
	HitCount = 0;
	Health = 100;
	DeathCount = 0;
	DisintegrationChance = 0;
	Damage = 10;
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

void AOrk_Character::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != NULL && OtherActor->ActorHasTag(TEXT("Player")) && IsAttacking == true)
	{
		AFireWarrior_Character* PlayerCharacter = Cast<AFireWarrior_Character>(OtherActor);
		PlayerCharacter->HitByChoppa();
		UE_LOG(LogTemp, Warning, TEXT("Hit"))
	}
}

void AOrk_Character::AttackInitiated()
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
			PlayAnimMontage(AttackMontageTwo, 1.0f);
			break;
		}
	}
}

void AOrk_Character::ComboAttackSave()
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
			PlayAnimMontage(AttackMontageTwo, 1.0f);
			break;
		}
	}
}

void AOrk_Character::ResetCombo()
{
	AttackCount = 0;
	SaveAttack = false;
	IsAttacking = false;
}

void AOrk_Character::HitByProjectile()
{
	if (!IsAttacking && Health > 0)
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
	}
	UpdateHealth();
}

void AOrk_Character::UpdateHealth()
{
	Health -= Damage;
	if (Health <= 0)
	{
		PlayAnimMontage(DeathMontage, 1.0f);
		this->DetachFromControllerPendingDestroy();
		this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DisintegrationChance = FMath::RandRange(0, 10);

		if (DisintegrationChance > 7)
		{
			Disintegration();
		}
	}
}

void AOrk_Character::Disintegration()
{
	for (int i = 0; i < 4; i++)
	{
		this->GetMesh()->CreateDynamicMaterialInstance(i);
		
	}
}