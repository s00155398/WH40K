// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWarrior_Character.h"
#include "DrawDebugHelpers.h"
#include "Engine\Classes\Components\AudioComponent.h"
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

	Health = 100;
	IsDead = false;

	AimTimelineCurve = CreateDefaultSubobject<UCurveFloat>(FName("Aim Curve"));
	AimTimelineCurve->FloatCurve.AddKey(0.0f,150.0f);
	AimTimelineCurve->FloatCurve.AddKey(0.2f, 10.0f);

	FOnTimelineFloat floatFunc{};
	floatFunc.BindUFunction(this, "AimTimelineFunc");

	AimTimeline.AddInterpFloat(AimTimelineCurve, floatFunc, FName("Aim function"));

	ConstructorHelpers::FObjectFinder<UAnimMontage> anim(TEXT("AnimMontage'/Game/FireCaste/Animations/Fire_Short_Montage.Fire_Short_Montage'"));

	FireMontage = anim.Object;


	IsOverHeating = false;

	OverHeatTimelineCurve = CreateDefaultSubobject<UCurveFloat>(FName("OverHeat Curve"));
	OverHeatTimelineCurve->FloatCurve.AddKey(0.0f, true);
	OverHeatTimelineCurve->FloatCurve.AddKey(3.0f, false);

	
	floatFunc.BindUFunction(this, "OverHeatTimelineFunc");

	OverHeatAimTimeline.AddInterpFloat(OverHeatTimelineCurve, floatFunc, FName("OverHeat function"));

	static ConstructorHelpers::FObjectFinder<USoundCue> OverHeatCue(
		TEXT("SoundCue'/Game/Audio/Plasma_Hiss_Cue.Plasma_Hiss_Cue'"));

	OverheatAudioCue = OverHeatCue.Object;

	OverheatAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("OverHeatAudioComp"));
	OverheatAudioComponent->bAutoActivate = false;

	OverheatAudioComponent->AttachTo(RootComponent);
	OverheatAudioComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	if (OverheatAudioCue->IsValidLowLevelFast()) 
	{
		OverheatAudioComponent->SetSound(OverheatAudioCue);
	}

	FireMode = 1;

	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimOne(TEXT("AnimMontage'/Game/FireCaste/Animations/HitReact_Front_Montage.HitReact_Front_Montage'"));
	HitMontageOne = HitAnimOne.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimTwo(TEXT("AnimMontage'/Game/FireCaste/Animations/HitReact_Back_Montage.HitReact_Back_Montage'"));
	HitMontageTwo = HitAnimTwo.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimThree(TEXT("AnimMontage'/Game/FireCaste/Animations/HitReact_Left_Montage.HitReact_Left_Montage'"));
	HitMontageThree = HitAnimThree.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimFour(TEXT("AnimMontage'/Game/FireCaste/Animations/HitReact_Right_Montage.HitReact_Right_Montage'"));
	HitMontageFour = HitAnimFour.Object;

	Damage = 0.1f;
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

	if (OverHeatAimTimeline.IsPlaying())
	{
		OverHeatAimTimeline.TickTimeline(DeltaTime);
	}

	if (IsOverHeating)
	{
		CoolDownSpeed = 0.9f;
	}
	else
	{
		CoolDownSpeed = 0.2f;
	}

	if (CarbineHeat > 0)
	{
		CarbineHeat -= CoolDownSpeed;
	}

	if (CarbineHeat >= 100)
	{
		IsOverHeating = true;
		OverheatAudioComponent->Play();
	}

	if (IsOverHeating == true && CarbineHeat <= 0)
	{
		IsOverHeating = false;
	}

}

// Called to bind functionality to input
void AFireWarrior_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Aim", IE_Pressed, this, &AFireWarrior_Character::Aim);
	InputComponent->BindAction("Aim", IE_Released, this, &AFireWarrior_Character::Aimout);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AFireWarrior_Character::CheckFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AFireWarrior_Character::StopFire);

	InputComponent->BindAction("ChangeFiringMode", IE_Pressed, this, &AFireWarrior_Character::ChangeFireMode);
}

void AFireWarrior_Character::Aim()
{
	IsAiming = true;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	AimTimeline.PlayFromStart();
}

void AFireWarrior_Character::Aimout()
{
	IsAiming = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	AimTimeline.Reverse();
}

void AFireWarrior_Character::AimTimelineFunc(float BoomArmLength)
{
	CameraBoom->TargetArmLength = BoomArmLength;
}

void AFireWarrior_Character::OverHeatTimelineFunc(float Duration)
{
	IsOverHeating = false;
}

void AFireWarrior_Character::Fire()
{	
	if (CarbineHeat + 10 >= 100)
	{
		OverheatAudioComponent->Play();
	}
	if (IsAiming == true && IsOverHeating != true)
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

	if (IsOverHeating != true && IsAiming)
	{
		CarbineHeat += 6;
	}
}

void AFireWarrior_Character::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
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

void AFireWarrior_Character::ChangeFireMode()
{
	switch (FireMode) {
	case 0:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fire Mode 1"));
		FireMode = 1;
		break;
	case 1:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fire Mode 0"));
		FireMode = 0;
		break;
	}
}

void AFireWarrior_Character::CheckFire()
{
	if (FireMode == 1) {
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AFireWarrior_Character::Fire, 0.15f, true, 0.01f);
	}
	else 
	{
		Fire();
	}
}

void AFireWarrior_Character::HitByEnemy()
{
	if (Health - Damage == 0)
	{
		Health -= Damage;
		IsDead = true;
		//InitiateCameraShake();
		GetController()->SetIgnoreMoveInput(true);
		this->DetachFromControllerPendingDestroy();
		this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		if (!IsAttacking)
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
		//InitiateCameraShake();
		Health -= 10;
	}
}

