// ==================================================
// Filename	:	NekoInterfaceInteract.h
// Author	:	22cu0214 JinWener
// Description:	Player interaction interface.
// Notes		:	
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NekoInterfaceInteract.generated.h"

UINTERFACE(MinimalAPI, Blueprintable) // add Blueprintable to make it valid for derived blueprint
class UNekoInterfaceInteract : public UInterface
{
	// This class does not need to be modified.
	GENERATED_BODY()
};

/**
 *
 */
class SHIRONEKOCPP_API INekoInterfaceInteract
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "Shironeko", BlueprintNativeEvent, BlueprintCallable)
	FString Interact();

};
