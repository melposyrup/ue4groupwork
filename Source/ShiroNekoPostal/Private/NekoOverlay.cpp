// Fill out your copyright notice in the Description page of Project Settings.


#include "NekoOverlay.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Animation/WidgetAnimation.h"

void UNekoOverlay::ShowCanvus(UCanvasPanel* canvus, bool bVisible)
{
	if (!canvus) return;

	if (bVisible)
	{
		canvus->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		canvus->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UNekoOverlay::IsCanvusVisible(UCanvasPanel* canvus)
{
	if (!canvus) return false;

	return canvus->IsVisible();
}