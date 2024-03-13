// Fill out your copyright notice in the Description page of Project Settings.


#include "NekoBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NekoCharacter.h"

/// <summary>
/// return NekoCharacter in the level of calling object
/// </summary>
/// <param name="WorldContextObject"> : calling object itself </param>
/// <returns></returns>
ANekoCharacter* UNekoBlueprintFunctionLibrary::GetNekoCharacter(UObject* WorldContextObject)
{
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, ANekoCharacter::StaticClass(), FoundCharacters);

	if (FoundCharacters.Num() > 0)
	{
		return Cast<ANekoCharacter>(FoundCharacters[0]);
	}
	return nullptr;
	//EXAMPLE:
	//ANekoCharacter* NekoCharacter = UNekoBlueprintFunctionLibrary::GetNekoCharacter(this);
}
