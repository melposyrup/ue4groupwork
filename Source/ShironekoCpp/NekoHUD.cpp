// Fill out your copyright notice in the Description page of Project Settings.


#include "NekoHUD.h"
#include "NekoOverlay.h"

void ANekoHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create the overlay
	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* Controller = World->GetFirstPlayerController();
	if (!Controller) return;

	if (OverlayClass)
	{
		Overlay = CreateWidget<UNekoOverlay>(Controller, OverlayClass);
		Overlay->AddToViewport();
	}
}
