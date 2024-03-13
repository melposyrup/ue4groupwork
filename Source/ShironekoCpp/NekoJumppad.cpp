// Fill out your copyright notice in the Description page of Project Settings.


#include "NekoJumppad.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NekoCharacter.h"

// Sets default values
ANekoJumppad::ANekoJumppad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(80.0f, 80.0f, 20.0f));
	BoxComponent->SetCollisionObjectType(ECC_WorldStatic);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -15.0f));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(60.0f);
	SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
}


void ANekoJumppad::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ANekoJumppad::OnSphereOverlap);
}

void ANekoJumppad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString ANekoJumppad::Interact_Implementation()
{
	return FString(TEXT("JumpPad"));
}

void ANekoJumppad::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANekoCharacter* Player = Cast<ANekoCharacter>(OtherActor);
	if (!Player) return;

	FVector LaunchDirection = GetActorUpVector();
	Player->OnJumpPad(LaunchDirection);
}
