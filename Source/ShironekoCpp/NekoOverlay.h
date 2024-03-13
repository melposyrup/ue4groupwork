// ==================================================
// Filename	:	NekoOverlay.h
// Author	:	22cu0214 JinWener
// Description:	
// Notes		:	
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NekoOverlay.generated.h"

class UOverlay;
class UCanvasPanel;
class UTextBlock;

UCLASS()
class SHIRONEKOCPP_API UNekoOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	//fuctions
	UFUNCTION(BlueprintCallable, Category = "Shironeko")
	void SetVisibilitySprintKey(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "Shironeko")
	void SetVisibilityMapKey(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "Shironeko")
	void SetVisibilityMapAndQuest(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "Shironeko")
	void UpdateLaunchCount(int32 launchCount);

	//!functions Implemented in WBP_NekoOverlay
	UFUNCTION(BlueprintImplementableEvent, Category = "Shironeko")
	void UpdateLaunchItemIcon(int32 launchCount);

	//!functions Implemented in WBP_NekoOverlay
	UFUNCTION(BlueprintImplementableEvent, Category = "Shironeko")
	void CreateQuestList();

	//!functions Implemented in WBP_NekoOverlay
	UFUNCTION(BlueprintImplementableEvent, Category = "Shironeko")
	void RemoveQuestList();

private:
	//!variables bind to WBP_NekoOverlay
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_sprintKey;

	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_mapKey;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Overlay_MapAndQuest;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_launchCount;

};
