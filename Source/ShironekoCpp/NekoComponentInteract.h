// ==================================================
// Filename	:	NekoComponentInteract.h
// Author	:	22cu0214 JinWener
// Description:	A custom ActorComponent attached to ANekoCharacter
// Notes		:	Implements the interact function by raycasting,
//				remember to add ObjectQueryParams mannually.
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NekoComponentInteract.generated.h"

class ANekoCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHIRONEKOCPP_API UNekoComponentInteract : public UActorComponent
{
	GENERATED_BODY()

	//override functions
public:	
	UNekoComponentInteract();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	//custom functions
public:
	FString Interact();

private:
	FHitResult Raycast();

private:
	ANekoCharacter* Owner;
};
