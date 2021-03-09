// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FireWarrior_Character.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Ork_Character.generated.h"


UCLASS()
class WH40K_API AOrk_Character : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	TArray<UInstancedStaticMeshComponent*> Instances;

	//Torso Meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* torsoOneMesh;

	// Boot Meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BootLeftMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BootRightMesh;

	// Helmet / Head Meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* FullHelmMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* HelmVisorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* JawGuardMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* PikkelHelmMesh;

	// Misc Meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BannerMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BackPackMesh;

	// Pauldron Meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* LeftPauldronOneMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* LeftPauldronTwoMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* RightPauldronOneMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* RightPauldronTwoMesh;


	//Torso Mesh Instance Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
		class UInstancedStaticMeshComponent* TorsoOneMeshInstance;

	// Boot Mesh Instance Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* BootLeftMeshInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* BootRightMeshInstance;

	// Helm Mesh Instance Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* FullHelmMeshInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* HelmetVisorMeshInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* JawGuardMeshInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* PikkelHelmMeshInstance;

	// Misc Mesh Instance Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* BannerMeshInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* BackPackMeshInstance;

	// Pauldron Mesh Instance Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* LeftPauldronOneMeshInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* LeftPauldronTwoMeshInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* RightPauldronOneMeshInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Static Meshes")
	class UInstancedStaticMeshComponent* RightPauldronTwoMeshInstance;

	

	AFireWarrior_Character* FireWarriorRef;

	UAnimMontage* AttackMontageOne;
	UAnimMontage* AttackMontageTwo;
	UAnimMontage* AttackMontageThree;
	UAnimMontage* AttackMontageFour;
	UAnimMontage* HitMontageOne;
	UAnimMontage* HitMontageTwo;
	UAnimMontage* HitMontageThree;
	UAnimMontage* HitMontageFour;
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool SaveAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool IsStunned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int AttackCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int HitCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int DeathCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		int DisintegrationChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float Damage;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UFUNCTION()
	void RandomizeActorScale(AActor* Actor);
	
	UFUNCTION()
	void SpawnOrkProps(AOrk_Character* OrkReference);
	
};
