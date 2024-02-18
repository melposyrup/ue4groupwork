// Fill out your copyright notice in the Description page of Project Settings.

#include "NekoAnimInstance.h"
#include "NekoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DebugHelper.h"


void UNekoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	NekoPlayer = Cast<ANekoCharacter>(TryGetPawnOwner());
	if (NekoPlayer) {
		PlayerMovement = NekoPlayer->GetCharacterMovement();
	}
}

void UNekoAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UNekoAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!NekoPlayer) return;
	if (!PlayerMovement)
	{
		//UE_LOG(LogTemp, Warning, TEXT("NOT FOUND CustomMovementComponent"));
		PlayerMovement = NekoPlayer->GetCharacterMovement();
	}

	if (!NekoPlayer || !PlayerMovement) return;

	GetGroundSpeed();
	GetAirSpeed();
	GetShouldMove();
	GetIsFalling();
}


void UNekoAnimInstance::GetGroundSpeed()
{
	GroundSpeed = UKismetMathLibrary::VSizeXY(NekoPlayer->GetVelocity());
}

void UNekoAnimInstance::GetAirSpeed()
{
	AirSpeed = NekoPlayer->GetVelocity().Z;
}

void UNekoAnimInstance::GetShouldMove()
{
	bShouldMove =
		PlayerMovement->GetCurrentAcceleration().Size() > 0 &&
		GroundSpeed > 5.f &&
		!bIsFalling;
}

void UNekoAnimInstance::GetIsFalling()
{
	bIsFalling = PlayerMovement->IsFalling();
}