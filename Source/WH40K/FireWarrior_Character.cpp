// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWarrior_Character.h"
#include "DrawDebugHelpers.h"
// Sets default values
AFireWarrior_Character::AFireWarrior_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);

	Carbine = CreateDefaultSubobject<UStaticMeshComponent>(FName("Carbine"));
	Carbine->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("CarbineSocket"));

	AimingArrow = CreateDefaultSubobject<UArrowComponent>(FName("Aiming Arrow"));
	AimingArrow->AttachToComponent(Carbine, FAttachmentTransformRules::KeepRelativeTransform);

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;


	TimelineCurve = CreateDefaultSubobject<UCurveFloat>(FName("Aim Curve"));
	TimelineCurve->FloatCurve.AddKey(0.0f,150.0f);
	TimelineCurve->FloatCurve.AddKey(0.2f, 10.0f);

	FOnTimelineFloat floatFunc{};
	floatFunc.BindUFunction(this, "AimTimelineFunc");

	AimTimeline.AddInterpFloat(TimelineCurve, floatFunc, FName("Aim function"));

	ConstructorHelpers::FObjectFinder<UAnimMontage> anim(TEXT("AnimMontage'/Game/FireCaste/Animations/Fire_Short_Montage.Fire_Short_Montage'"));

	
	FireMontage = anim.Object;
}

// Called when the game starts or when spawned
void AFireWarrior_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFireWarrior_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AimTimeline.IsPlaying())
	{
		AimTimeline.TickTimeline(DeltaTime);
	}

	if (CarbineHeat > 0)
	{
		CarbineHeat -= 0.1f;
	}

}

// Called to bind functionality to input
void AFireWarrior_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Aim", IE_Pressed, this, &AFireWarrior_Character::Aim);
	InputComponent->BindAction("Aim", IE_Released, this, &AFireWarrior_Character::Aimout);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AFireWarrior_Character::Fire);
}

void AFireWarrior_Character::Aim()
{
	IsAiming = true;
	bUseControllerRotationYaw = true;

	AimTimeline.PlayFromStart();

}

void AFireWarrior_Character::Aimout()
{
	IsAiming = false;
	bUseControllerRotationYaw = false;
	AimTimeline.Reverse();
}

void AFireWarrior_Character::AimTimelineFunc(float BoomArmLength)
{
	CameraBoom->TargetArmLength = BoomArmLength;
}

void AFireWarrior_Character::Fire()
{	
	if (IsAiming == true)
	{
		if (IsAttacking == true)
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
				PlayAnimMontage(FireMontage,1.0f);
				FireProjectile();
				break;
			case 1:
				
				AttackCount = 0;
				PlayAnimMontage(FireMontage, 1.0f);
				FireProjectile();
				break;
			}
		}
	}
	if (CarbineHeat < 100 && (CarbineHeat + 10) < 100 && IsAiming)
	{
		CarbineHeat += 10;
	}
}

void AFireWarrior_Character::ResetCombo()
{
	AttackCount = 0;
	SaveAttack = false;
	IsAttacking = false;
}

void AFireWarrior_Character::ComboAttackSave()
{
	if (SaveAttack)
	{
		SaveAttack = false;
		switch (AttackCount)
		{
		case 0:
			AttackCount = 1;
			PlayAnimMontage(FireMontage, 1.0f);
			FireProjectile();
			break;

		case 1:
			AttackCount = 0;
			PlayAnimMontage(FireMontage, 1.0f);
			FireProjectile();
			break;
		}
	}
}




