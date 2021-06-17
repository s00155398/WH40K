// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character.h"
#include <WH40K/Ork_Character_ShootaBoy.h>
#include <WH40K/Ork_Character_OrkBoy.h>
// Sets default values
AOrk_Character::AOrk_Character(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TorsoOneMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Torso One Mesh Instances"));
	TorsoTwoMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Torso Two Mesh Instances"));
	TorsoThreeMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Torso Three Mesh Instances"));
	TorsoFourMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Torso Four Mesh Instances"));

	BootLeftMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Boot Left Mesh Instances"));
	BootRightMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Boot Right Mesh Instances"));

	FullHelmMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Full Helm Mesh Instances"));
	HelmetVisorMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Helmet Visor Mesh Instances"));
	PikkelHelmMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Pikkel Helmet Mesh Instances"));
	GoggleHelmMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Goggle Helm Mesh Instances"));
	JawGuardMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Jaw Guard Mesh Instances"));

	BannerMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Banner Mesh Instances"));
	BackPackMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("BackPack Mesh Instances"));

	LeftPauldronOneMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Left Pauldron One Mesh Instances"));
	LeftPauldronTwoMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Left Pauldron Two Mesh Instances"));
	RightPauldronOneMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Right Pauldron One Mesh Instances"));
	RightPauldronTwoMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Right Pauldron Two Mesh Instances"));


	ConstructorHelpers::FObjectFinder<UStaticMesh> TorsoOneStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Torso/torso_armor_one.torso_armor_one'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TorsoTwoStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Torso/torso_armor_two.torso_armor_two'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TorsoThreeStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Torso/torso_armor_three.torso_armor_three'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TorsoFourStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Torso/torso_armor_four.torso_armor_four'"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> BootLeftStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Boots/bootArmorLeft.bootArmorLeft'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BootRightStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Boots/bootArmorRight.bootArmorRight'"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> FullHelmStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/FullHelm.FullHelm'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> HelmVisorStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/HelmetWVisor.HelmetWVisor'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> JawGuardStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/JawGuard.JawGuard'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> PikkelHelmStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/PikkelHelm.PikkelHelm'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> GoggleHelmStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/GoggleHelm.GoggleHelm'"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> BannerStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Misc/Banner.Banner'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BackPackStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Misc/pack.pack'"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> LeftPauldronOneStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Pauldrons/LeftPauldronOne.LeftPauldronOne'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> LeftPauldronTwoStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Pauldrons/LeftPauldronTwo.LeftPauldronTwo'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> RightPauldronOneStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Pauldrons/RightPauldronOne.RightPauldronOne'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> RightPauldronTwoStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Pauldrons/RightPauldronTwo.RightPauldronTwo'"));

	TorsoOneMeshInstance->SetupAttachment(GetMesh(), FName("torso_armor_one"));
	TorsoTwoMeshInstance->SetupAttachment(GetMesh(), FName("torso_armor_two"));
	TorsoThreeMeshInstance->SetupAttachment(GetMesh(), FName("torso_armor_three"));
	TorsoFourMeshInstance->SetupAttachment(GetMesh(), FName("torso_armor_four"));

	BootLeftMeshInstance->SetupAttachment(GetMesh(), FName("boot_left_socket"));
	BootRightMeshInstance->SetupAttachment(GetMesh(), FName("boot_rightsocket"));

	FullHelmMeshInstance->SetupAttachment(GetMesh(), FName("fullhelmsocket"));
	HelmetVisorMeshInstance->SetupAttachment(GetMesh(), FName("helmWvisorSocket"));
	PikkelHelmMeshInstance->SetupAttachment(GetMesh(), FName("pikkelhelmsocket"));
	JawGuardMeshInstance->SetupAttachment(GetMesh(), FName("jawsocket"));
	GoggleHelmMeshInstance->SetupAttachment(GetMesh(), FName("goggleHelmSocket"));

	BannerMeshInstance->SetupAttachment(GetMesh(), FName("bannerSocket"));
	BackPackMeshInstance->SetupAttachment(GetMesh(), FName("backpackSocket"));

	LeftPauldronOneMeshInstance->SetupAttachment(GetMesh(), FName("leftPauldronSocket"));
	LeftPauldronTwoMeshInstance->SetupAttachment(GetMesh(), FName("leftPauldronSocket"));
	RightPauldronOneMeshInstance->SetupAttachment(GetMesh(), FName("rightPauldronSocket"));
	RightPauldronTwoMeshInstance->SetupAttachment(GetMesh(), FName("rightPauldronSocket"));

	torsoOneMesh = TorsoOneStaticMesh.Object;
	torsoTwoMesh = TorsoTwoStaticMesh.Object;
	torsoThreeMesh = TorsoThreeStaticMesh.Object;
	torsoFourMesh = TorsoFourStaticMesh.Object;

	BootLeftMesh = BootLeftStaticMesh.Object;
	
	BootRightMesh = BootRightStaticMesh.Object;

	FullHelmMesh = FullHelmStaticMesh.Object;
	HelmVisorMesh = HelmVisorStaticMesh.Object;
	JawGuardMesh = JawGuardStaticMesh.Object;
	PikkelHelmMesh = PikkelHelmStaticMesh.Object;
	GoggleHelmMesh = GoggleHelmStaticMesh.Object;

	BannerMesh = BannerStaticMesh.Object;
	BackPackMesh = BackPackStaticMesh.Object;
	
	LeftPauldronOneMesh = LeftPauldronOneStaticMesh.Object;
	LeftPauldronTwoMesh = LeftPauldronTwoStaticMesh.Object;
	RightPauldronOneMesh = RightPauldronOneStaticMesh.Object;
	RightPauldronTwoMesh = RightPauldronTwoStaticMesh.Object;
	IsStunned = false;
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

void AOrk_Character::RandomizeActorScale(AOrk_Character* OrkReference)
{
	float RanScaleRange = UKismetMathLibrary::RandomFloatInRange(0.9f, 1.3f);
	FVector NewScale = { RanScaleRange ,RanScaleRange , RanScaleRange };
	
	OrkReference->Health *= RanScaleRange;
	OrkReference->SetActorRelativeScale3D(NewScale);
}

void AOrk_Character::SpawnOrkProps(AOrk_Character* OrkReference)
{
	int ranNum = 0;

	if (OrkReference)
	{
		FTransform InstanceTransform;
		
#pragma region Torso Prop generation
		ranNum = UKismetMathLibrary::RandomIntegerInRange(0, 4);
		switch (ranNum)
		{
		case 0:
			TorsoOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			TorsoOneMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("torso_armor_one"));
			TorsoOneMeshInstance->RegisterComponent();
			TorsoOneMeshInstance->SetStaticMesh(torsoOneMesh);

			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);

			TorsoOneMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(TorsoOneMeshInstance);
			break;

		case 1:
			TorsoTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			TorsoTwoMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("torso_armor_two"));
			TorsoTwoMeshInstance->RegisterComponent();
			TorsoTwoMeshInstance->SetStaticMesh(torsoTwoMesh);

			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);

			TorsoTwoMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(TorsoTwoMeshInstance);
			break;

		case 2:
			TorsoThreeMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			TorsoThreeMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("torso_armor_three"));
			TorsoThreeMeshInstance->RegisterComponent();
			TorsoThreeMeshInstance->SetStaticMesh(torsoThreeMesh);

			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);

			TorsoThreeMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(TorsoThreeMeshInstance);
			break;

		case 3:
			TorsoFourMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			TorsoFourMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("torso_armor_four"));
			TorsoFourMeshInstance->RegisterComponent();
			TorsoFourMeshInstance->SetStaticMesh(torsoFourMesh);

			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);

			TorsoFourMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(TorsoFourMeshInstance);
			break;

		case 4:
			break;
		}
#pragma endregion

#pragma region Boot Prop Generation
		BootLeftMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
		BootLeftMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("boot_left_socket"));
		BootLeftMeshInstance->RegisterComponent();
		BootLeftMeshInstance->SetStaticMesh(BootLeftMesh);

		InstanceTransform.SetLocation(FVector::ZeroVector);
		InstanceTransform.SetRotation(FQuat::Identity);

		BootLeftMeshInstance->AddInstance(InstanceTransform);


		BootRightMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
		BootRightMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("boot_rightsocket"));
		BootRightMeshInstance->RegisterComponent();
		BootRightMeshInstance->SetStaticMesh(BootRightMesh);

		InstanceTransform.SetLocation(FVector::ZeroVector);
		InstanceTransform.SetRotation(FQuat::Identity);

		BootRightMeshInstance->AddInstance(InstanceTransform);

		OrkReference->Instances.Add(BootRightMeshInstance);
		OrkReference->Instances.Add(BootLeftMeshInstance);
#pragma endregion

#pragma region Helmet Prop Generation

		ranNum = UKismetMathLibrary::RandomIntegerInRange(0, 5);
		switch (ranNum)
		{
		case 0:
			FullHelmMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			FullHelmMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("fullhelmsocket"));
			FullHelmMeshInstance->RegisterComponent();
			FullHelmMeshInstance->SetStaticMesh(FullHelmMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			FullHelmMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(FullHelmMeshInstance);
			break;
		case 1:
			HelmetVisorMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			HelmetVisorMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("helmWvisorSocket"));
			HelmetVisorMeshInstance->RegisterComponent();
			HelmetVisorMeshInstance->SetStaticMesh(HelmVisorMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			HelmetVisorMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(HelmetVisorMeshInstance);
			break;
		case 2:
			JawGuardMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			JawGuardMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("jawsocket"));
			JawGuardMeshInstance->RegisterComponent();
			JawGuardMeshInstance->SetStaticMesh(JawGuardMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			JawGuardMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(JawGuardMeshInstance);
			break;
		case 3:
			PikkelHelmMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			PikkelHelmMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("pikkelhelmsocket"));
			PikkelHelmMeshInstance->RegisterComponent();
			PikkelHelmMeshInstance->SetStaticMesh(PikkelHelmMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			PikkelHelmMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(PikkelHelmMeshInstance);
			break;
		case 4:
			GoggleHelmMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			GoggleHelmMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("goggleHelmSocket"));
			GoggleHelmMeshInstance->RegisterComponent();
			GoggleHelmMeshInstance->SetStaticMesh(GoggleHelmMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			GoggleHelmMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(GoggleHelmMeshInstance);
			break;

		case 5:
			break;
		}
#pragma endregion

#pragma region Misc Prop Generation
		ranNum = UKismetMathLibrary::RandomIntegerInRange(0, 10);
		if (ranNum > 9)
		{
			BannerMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			BannerMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("bannerSocket"));
			BannerMeshInstance->RegisterComponent();
			BannerMeshInstance->SetStaticMesh(BannerMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			BannerMeshInstance->AddInstance(InstanceTransform);
			Instances.Add(BannerMeshInstance);

			OrkReference->Instances.Add(BannerMeshInstance);
		}
		else
		{
			ranNum = UKismetMathLibrary::RandomIntegerInRange(0, 1);
			switch (ranNum)
			{
			case 0:
				break;
			case 1:
				BackPackMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
				BackPackMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("backpackSocket"));
				BackPackMeshInstance->RegisterComponent();
				BackPackMeshInstance->SetStaticMesh(BackPackMesh);
				InstanceTransform.SetLocation(FVector::ZeroVector);
				InstanceTransform.SetRotation(FQuat::Identity);
				BackPackMeshInstance->AddInstance(InstanceTransform);

				OrkReference->Instances.Add(BackPackMeshInstance);

				break;
			}
		}
#pragma endregion

#pragma region Pauldron Mesh 

		ranNum = UKismetMathLibrary::RandomIntegerInRange(0, 5);

		switch (ranNum)
		{
		case 0:
			LeftPauldronOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			LeftPauldronOneMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("leftPauldronSocket"));
			LeftPauldronOneMeshInstance->RegisterComponent();
			LeftPauldronOneMeshInstance->SetStaticMesh(LeftPauldronOneMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			LeftPauldronOneMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(LeftPauldronOneMeshInstance);
			

			break;
		case 1:
			LeftPauldronTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			LeftPauldronTwoMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("leftPauldronSocket"));
			LeftPauldronTwoMeshInstance->RegisterComponent();
			LeftPauldronTwoMeshInstance->SetStaticMesh(LeftPauldronTwoMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			LeftPauldronTwoMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(LeftPauldronTwoMeshInstance);
			

			break;
		case 2:
			RightPauldronOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			RightPauldronOneMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("rightPauldronSocket"));
			RightPauldronOneMeshInstance->RegisterComponent();
			RightPauldronOneMeshInstance->SetStaticMesh(RightPauldronOneMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			RightPauldronOneMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(RightPauldronOneMeshInstance);
			

			break;
		case 3:
			RightPauldronTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			RightPauldronTwoMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("rightPauldronSocket"));
			RightPauldronTwoMeshInstance->RegisterComponent();
			RightPauldronTwoMeshInstance->SetStaticMesh(RightPauldronTwoMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			RightPauldronTwoMeshInstance->AddInstance(InstanceTransform);

			OrkReference->Instances.Add(RightPauldronTwoMeshInstance);
	
			break;
		case 4:
			LeftPauldronOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			LeftPauldronOneMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("leftPauldronSocket"));
			LeftPauldronOneMeshInstance->RegisterComponent();
			LeftPauldronOneMeshInstance->SetStaticMesh(LeftPauldronOneMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			LeftPauldronOneMeshInstance->AddInstance(InstanceTransform);


			RightPauldronOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			RightPauldronOneMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("rightPauldronSocket"));
			RightPauldronOneMeshInstance->RegisterComponent();
			RightPauldronOneMeshInstance->SetStaticMesh(RightPauldronOneMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			RightPauldronOneMeshInstance->AddInstance(InstanceTransform);

		
			OrkReference->Instances.Add(LeftPauldronOneMeshInstance);
			OrkReference->Instances.Add(RightPauldronOneMeshInstance);
			
			break;
		case 5:
			LeftPauldronTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			LeftPauldronTwoMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("leftPauldronSocket"));
			LeftPauldronTwoMeshInstance->RegisterComponent();
			LeftPauldronTwoMeshInstance->SetStaticMesh(LeftPauldronTwoMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			LeftPauldronTwoMeshInstance->AddInstance(InstanceTransform);

			RightPauldronTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(OrkReference->GetMesh());
			RightPauldronTwoMeshInstance->SetupAttachment(OrkReference->GetMesh(), FName("rightPauldronSocket"));
			RightPauldronTwoMeshInstance->RegisterComponent();
			RightPauldronTwoMeshInstance->SetStaticMesh(RightPauldronTwoMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			RightPauldronTwoMeshInstance->AddInstance(InstanceTransform);

			
			OrkReference->Instances.Add(LeftPauldronTwoMeshInstance);
			OrkReference->Instances.Add(RightPauldronTwoMeshInstance);
			
			break;
		}
#pragma endregion
	}
	for (int i = 0; i < OrkReference->Instances.Num(); i++)
	{
		OrkReference->Instances[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void AOrk_Character::projectileHit(AOrk_Character* OrkReference, float damageInflicted)
{
	if (damageInflicted > 40)
	{
		OrkReference->IsStunned = true;
	}
}


