// Fill out your copyright notice in the Description page of Project Settings.


#include "NekoLaunchItem.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ANekoLaunchItem::ANekoLaunchItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(100.0f);
	SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void ANekoLaunchItem::BeginPlay()
{
	Super::BeginPlay();
}

void ANekoLaunchItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotate Item around Z axis (change yaw)
	{
		FRotator RotationDelta(0.0f, RotationSpeed * DeltaTime, 0.0f);
		AddActorLocalRotation(RotationDelta);
	}
}

