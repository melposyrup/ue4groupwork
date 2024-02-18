// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NekoOverlay.generated.h"

class UCanvasPanel;
class UTextBlock;
class UHorizontalBox;
class UWidgetAnimation;

UCLASS()
class SHIRONEKOPOSTAL_API UNekoOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//todo functions for Stamina, Sense, Points(Money)
	UFUNCTION(BlueprintCallable)
	void ShowCanvus(UCanvasPanel* canvus, bool bVisible);

	UFUNCTION(BlueprintCallable)
	bool IsCanvusVisible(UCanvasPanel* canvus);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateQuestWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void DeleteQuestWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowMapTutorialBox(bool IsVisible);

private:

	/** Overylay Box wrapped Stamina, Sense, Money, Minimap*/
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Overlay;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Currency;

	/** Map and Quest */
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MapAndQuest;

	/** Inventory */

public:
	FORCEINLINE UCanvasPanel* GetMap() const { return MapAndQuest; }

};
