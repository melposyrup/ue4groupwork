// ==================================================
// Filename	:	NekoBlueprintFunctionLibrary.h
// Author	:	22cu0214 JinWener
// Description:	
// Notes		:	UBlueprintFunctionLibrary CANNOT be derived to BP.
//				Use BP_FunctionLibrary in editor instead.
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NekoBlueprintFunctionLibrary.generated.h"


class ANekoCharacter;

UCLASS()
class SHIRONEKOCPP_API UNekoBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Shironeko")
	static ANekoCharacter* GetNekoCharacter(UObject* WorldContextObject);
};
