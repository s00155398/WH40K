// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character.h"

// Sets default values
AOrk_Character::AOrk_Character(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BootLeftMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Boot Left Mesh Instances"));
	BootRightMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Boot Right Mesh Instances"));
	FullHelmMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Full Helm Mesh Instances"));
	HelmetVisorMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Helmet Visor Mesh Instances"));
	PikkelHelmMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Pikkel Helmet Mesh Instances"));
	JawGuardMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Jaw Guard Mesh Instances"));
	BannerMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Banner Mesh Instances"));
	BackPackMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("BackPack Mesh Instances"));
	LeftPauldronOneMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Left Pauldron One Mesh Instances"));
	LeftPauldronTwoMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Left Pauldron Two Mesh Instances"));
	RightPauldronOneMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Right Pauldron One Mesh Instances"));
	RightPauldronTwoMeshInstance = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Right Pauldron Two Mesh Instances"));


	ConstructorHelpers::FObjectFinder<UStaticMesh> BootLeftStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Boots/bootArmorLeft.bootArmorLeft'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BootRightStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Boots/bootArmorRight.bootArmorRight'"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> FullHelmStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/FullHelm.FullHelm'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> HelmVisorStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/HelmetWVisor.HelmetWVisor'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> JawGuardStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/JawGuard.JawGuard'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> PikkelHelmStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Helmets/PikkelHelm.PikkelHelm'"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> BannerStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Misc/Banner.Banner'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BackPackStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Misc/pack.pack'"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> LeftPauldronOneStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Pauldrons/LeftPauldronOne.LeftPauldronOne'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> LeftPauldronTwoStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Pauldrons/LeftPauldronTwo.LeftPauldronTwo'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> RightPauldronOneStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Pauldrons/RightPauldronOne.RightPauldronOne'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> RightPauldronTwoStaticMesh(TEXT("StaticMesh'/Game/ork/Props/Pauldrons/RightPauldronTwo.RightPauldronTwo'"));

	BootLeftMeshInstance->SetupAttachment(GetMesh(), FName("boot_left_socket"));
	BootRightMeshInstance->SetupAttachment(GetMesh(), FName("boot_rightsocket"));

	FullHelmMeshInstance->SetupAttachment(GetMesh(), FName("fullhelmsocket"));
	HelmetVisorMeshInstance->SetupAttachment(GetMesh(), FName("helmWvisorSocket"));
	PikkelHelmMeshInstance->SetupAttachment(GetMesh(), FName("pikkelhelmsocket"));
	JawGuardMeshInstance->SetupAttachment(GetMesh(), FName("jawsocket"));

	BannerMeshInstance->SetupAttachment(GetMesh(), FName("bannerSocket"));
	BackPackMeshInstance->SetupAttachment(GetMesh(), FName("backpackSocket"));

	LeftPauldronOneMeshInstance->SetupAttachment(GetMesh(), FName("leftPauldronSocket"));
	LeftPauldronTwoMeshInstance->SetupAttachment(GetMesh(), FName("leftPauldronSocket"));
	RightPauldronOneMeshInstance->SetupAttachment(GetMesh(), FName("rightPauldronSocket"));
	RightPauldronTwoMeshInstance->SetupAttachment(GetMesh(), FName("rightPauldronSocket"));

	
	BootLeftMesh = BootLeftStaticMesh.Object;
	
	BootRightMesh = BootRightStaticMesh.Object;

	FullHelmMesh = FullHelmStaticMesh.Object;
	HelmVisorMesh = HelmVisorStaticMesh.Object;
	JawGuardMesh = JawGuardStaticMesh.Object;
	PikkelHelmMesh = PikkelHelmStaticMesh.Object;

	BannerMesh = BannerStaticMesh.Object;
	BackPackMesh = BackPackStaticMesh.Object;
	
	LeftPauldronOneMesh = LeftPauldronOneStaticMesh.Object;
	LeftPauldronTwoMesh = LeftPauldronTwoStaticMesh.Object;
	RightPauldronOneMesh = RightPauldronOneStaticMesh.Object;
	RightPauldronTwoMesh = RightPauldronTwoStaticMesh.Object;
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

void AOrk_Character::RandomizeActorScale(AActor* Actor)
{
	float RanScaleRange = UKismetMathLibrary::RandomFloatInRange(0.9f, 1.3f);
	FVector NewScale = { RanScaleRange ,RanScaleRange , RanScaleRange };

	Actor->SetActorRelativeScale3D(NewScale);
}

void AOrk_Character::SpawnOrkMeshProps(USkeletalMeshComponent* MeshTarget)
{
	int ranNum = 0;
	
	if (MeshTarget)
	{	
		BootLeftMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
		BootLeftMeshInstance->SetupAttachment(MeshTarget, FName("boot_left_socket"));
		BootLeftMeshInstance->RegisterComponent();
		BootLeftMeshInstance->SetStaticMesh(BootLeftMesh);

		FTransform InstanceTransform;
		InstanceTransform.SetLocation(FVector::ZeroVector);
		InstanceTransform.SetRotation(FQuat::Identity);

		BootLeftMeshInstance->AddInstance(InstanceTransform);

		BootRightMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
		BootRightMeshInstance->SetupAttachment(MeshTarget, FName("boot_rightsocket"));
		BootRightMeshInstance->RegisterComponent();
		BootRightMeshInstance->SetStaticMesh(BootRightMesh);

		InstanceTransform.SetLocation(FVector::ZeroVector);
		InstanceTransform.SetRotation(FQuat::Identity);

		BootRightMeshInstance->AddInstance(InstanceTransform);


#pragma region Helmet Prop Generation

		ranNum = UKismetMathLibrary::RandomIntegerInRange(0, 4);
		switch (ranNum)
		{
		case 0:
			FullHelmMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			FullHelmMeshInstance->SetupAttachment(MeshTarget, FName("fullhelmsocket"));
			FullHelmMeshInstance->RegisterComponent();
			FullHelmMeshInstance->SetStaticMesh(FullHelmMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			FullHelmMeshInstance->AddInstance(InstanceTransform);
			break;
		case 1:
			HelmetVisorMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			HelmetVisorMeshInstance->SetupAttachment(MeshTarget, FName("helmWvisorSocket"));
			HelmetVisorMeshInstance->RegisterComponent();
			HelmetVisorMeshInstance->SetStaticMesh(HelmVisorMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			HelmetVisorMeshInstance->AddInstance(InstanceTransform);
			break;
		case 2:
			JawGuardMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			JawGuardMeshInstance->SetupAttachment(MeshTarget, FName("jawsocket"));
			JawGuardMeshInstance->RegisterComponent();
			JawGuardMeshInstance->SetStaticMesh(JawGuardMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			JawGuardMeshInstance->AddInstance(InstanceTransform);
			break;
		case 3:
			PikkelHelmMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			PikkelHelmMeshInstance->SetupAttachment(MeshTarget, FName("pikkelhelmsocket"));
			PikkelHelmMeshInstance->RegisterComponent();
			PikkelHelmMeshInstance->SetStaticMesh(PikkelHelmMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			PikkelHelmMeshInstance->AddInstance(InstanceTransform);
			break;
		case 4:
			break;
		}
#pragma endregion

#pragma region Misc Prop Generation
		ranNum = UKismetMathLibrary::RandomIntegerInRange(0, 2);
		switch (ranNum)
		{
		case 0:
			BannerMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			BannerMeshInstance->SetupAttachment(MeshTarget, FName("bannerSocket"));
			BannerMeshInstance->RegisterComponent();
			BannerMeshInstance->SetStaticMesh(BannerMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			BannerMeshInstance->AddInstance(InstanceTransform);
			break;
		case 1:
			BackPackMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			BackPackMeshInstance->SetupAttachment(MeshTarget, FName("backpackSocket"));
			BackPackMeshInstance->RegisterComponent();
			BackPackMeshInstance->SetStaticMesh(BackPackMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			BackPackMeshInstance->AddInstance(InstanceTransform);
			break;
		case 2:
			break;
		}
#pragma endregion

#pragma region Pauldron Mesh 

		ranNum = UKismetMathLibrary::RandomIntegerInRange(0, 6);

		switch (ranNum)
		{
		case 0:
			LeftPauldronOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			LeftPauldronOneMeshInstance->SetupAttachment(MeshTarget, FName("leftPauldronSocket"));
			LeftPauldronOneMeshInstance->RegisterComponent();
			LeftPauldronOneMeshInstance->SetStaticMesh(LeftPauldronOneMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			LeftPauldronOneMeshInstance->AddInstance(InstanceTransform);
			break;
		case 1:
			LeftPauldronTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			LeftPauldronTwoMeshInstance->SetupAttachment(MeshTarget, FName("leftPauldronSocket"));
			LeftPauldronTwoMeshInstance->RegisterComponent();
			LeftPauldronTwoMeshInstance->SetStaticMesh(LeftPauldronTwoMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			LeftPauldronTwoMeshInstance->AddInstance(InstanceTransform);
			break;
		case 2:
			RightPauldronOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			RightPauldronOneMeshInstance->SetupAttachment(MeshTarget, FName("rightPauldronSocket"));
			RightPauldronOneMeshInstance->RegisterComponent();
			RightPauldronOneMeshInstance->SetStaticMesh(RightPauldronOneMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			RightPauldronOneMeshInstance->AddInstance(InstanceTransform);
			break;
		case 3:
			RightPauldronTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			RightPauldronTwoMeshInstance->SetupAttachment(MeshTarget, FName("rightPauldronSocket"));
			RightPauldronTwoMeshInstance->RegisterComponent();
			RightPauldronTwoMeshInstance->SetStaticMesh(RightPauldronTwoMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			RightPauldronTwoMeshInstance->AddInstance(InstanceTransform);
			break;
		case 4:
			LeftPauldronOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			LeftPauldronOneMeshInstance->SetupAttachment(MeshTarget, FName("leftPauldronSocket"));
			LeftPauldronOneMeshInstance->RegisterComponent();
			LeftPauldronOneMeshInstance->SetStaticMesh(LeftPauldronOneMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			LeftPauldronOneMeshInstance->AddInstance(InstanceTransform);

			RightPauldronOneMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			RightPauldronOneMeshInstance->SetupAttachment(MeshTarget, FName("rightPauldronSocket"));
			RightPauldronOneMeshInstance->RegisterComponent();
			RightPauldronOneMeshInstance->SetStaticMesh(RightPauldronOneMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			RightPauldronOneMeshInstance->AddInstance(InstanceTransform);
			break;
		case 5:
			LeftPauldronTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			LeftPauldronTwoMeshInstance->SetupAttachment(MeshTarget, FName("leftPauldronSocket"));
			LeftPauldronTwoMeshInstance->RegisterComponent();
			LeftPauldronTwoMeshInstance->SetStaticMesh(LeftPauldronTwoMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			LeftPauldronTwoMeshInstance->AddInstance(InstanceTransform);
			break;
		case 6:
			RightPauldronTwoMeshInstance = NewObject<UInstancedStaticMeshComponent>(MeshTarget);
			RightPauldronTwoMeshInstance->SetupAttachment(MeshTarget, FName("rightPauldronSocket"));
			RightPauldronTwoMeshInstance->RegisterComponent();
			RightPauldronTwoMeshInstance->SetStaticMesh(RightPauldronTwoMesh);
			InstanceTransform.SetLocation(FVector::ZeroVector);
			InstanceTransform.SetRotation(FQuat::Identity);
			RightPauldronTwoMeshInstance->AddInstance(InstanceTransform);
			break;
		}
	}
#pragma endregion



}