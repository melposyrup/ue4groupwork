// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NekoCharacter.generated.h"

UCLASS()
class SHIRONEKOPOSTAL_API ANekoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Override functions */
	ANekoCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	/** Input */
	/** PlayerMovement */
	void MoveForward(float Value);
	void MoveRight(float Value);


	/** UI */
	void OverlayInit();
	void MapOverlayOnOff();

private:
	/** Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ViewCamera;

	// MinimapCameraBoom, MinimapCamera, PlayerIcon are in the BP_NekoCharacter


	/** UI */
	UPROPERTY()
	class UNekoOverlay* Overlay;

};
