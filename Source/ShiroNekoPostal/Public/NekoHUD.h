// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NekoHUD.generated.h"

class UNekoOverlay;

UCLASS()
class SHIRONEKOPOSTAL_API ANekoHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Neko)
	TSubclassOf<UNekoOverlay> OverlayClass;

	UPROPERTY()
	UNekoOverlay* Overlay;

	UFUNCTION()
	void CreateOverlay();

public:
	UFUNCTION(BlueprintCallable)
	UNekoOverlay* GetNekoOverlay() const { return Overlay; }
};
