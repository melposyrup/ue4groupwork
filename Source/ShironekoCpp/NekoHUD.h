// ==================================================
// Filename	:	NekoHUD.h
// Author	:	22cu0214 JinWener
// Description:	Derived to BP_NekoHUD as a part of BP_NekoGameModePlay.
//				Provides a HUD pointer to ANekoCharacter.
// Notes		:	
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NekoHUD.generated.h"

/**
 * 
 */

UCLASS()
class SHIRONEKOCPP_API ANekoHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	class UNekoOverlay* GetNekoOverlay() const { return Overlay; }

private:
	//!setup BP_NekoOverlay in BP_NekoHUD
	UPROPERTY(EditDefaultsOnly, Category = "Shironeko")
	TSubclassOf<UNekoOverlay> OverlayClass;

	UPROPERTY()
	UNekoOverlay* Overlay;

};
