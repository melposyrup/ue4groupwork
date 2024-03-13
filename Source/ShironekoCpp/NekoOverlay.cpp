
#include "NekoOverlay.h"
#include "Components/Overlay.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h" 

void UNekoOverlay::SetVisibilityMapKey(bool bVisible)
{
	if (bVisible) {
		Overlay_mapKey->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else {
		Overlay_mapKey->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UNekoOverlay::SetVisibilitySprintKey(bool bVisible)
{
	if (bVisible) {
		Overlay_sprintKey->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else {
		Overlay_sprintKey->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UNekoOverlay::SetVisibilityMapAndQuest(bool bVisible)
{
	if (bVisible) {
		Overlay_MapAndQuest->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CreateQuestList();
	}
	else {
		Overlay_MapAndQuest->SetVisibility(ESlateVisibility::Collapsed);
		RemoveQuestList();
	}
}

void UNekoOverlay::UpdateLaunchCount(int32 launchCount)
{
	if (!TextBlock_launchCount) return;

	FText LaunchCountText = FText::AsNumber(launchCount);
	TextBlock_launchCount->SetText(LaunchCountText);
	UpdateLaunchItemIcon(launchCount);
}
