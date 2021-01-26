// Fill out your copyright notice in the Description page of Project Settings.


#include "Ork_Character_ShootaBoy.h"
AOrk_Character_ShootaBoy::AOrk_Character_ShootaBoy()
{
	Shoota = CreateDefaultSubobject<UStaticMeshComponent>(FName("Shoota"));
	Shoota->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("Shoota_Socket"));

	IsAiming = false;
	IsFiring = false;

	ammo = 10;
}


