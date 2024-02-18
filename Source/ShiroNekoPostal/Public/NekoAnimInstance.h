// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NekoAnimInstance.generated.h"

class ANekoCharacter;
class UCharacterMovementComponent;

UCLASS()
class SHIRONEKOPOSTAL_API UNekoAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY()
	ANekoCharacter* NekoPlayer;

	UPROPERTY()
	UCharacterMovementComponent* PlayerMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;
	void GetGroundSpeed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	float AirSpeed;
	void GetAirSpeed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;
	void GetShouldMove();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;
	void GetIsFalling();

};
