// ==================================================
// Filename	:	NekoLaunchItem.h
// Author	:	22cu0214 JinWener
// Description:	
// Notes		:	
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NekoLaunchItem.generated.h"

UCLASS()
class SHIRONEKOCPP_API ANekoLaunchItem : public AActor
{
	GENERATED_BODY()
	
	//override function
public:	
	ANekoLaunchItem();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	//custom variable
	UPROPERTY(VisibleAnywhere, Category = "Shironeko")
	class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Shironeko")
	class USphereComponent* SphereComponent; //for overlap

	//!Implemented in BP: 
	//! when overlapped with player,
	//! call player.LaunchItemCountIncrease()
	//! play sound and effect
	//! Destroy() 
	
	UPROPERTY(EditAnywhere, Category = "Shironeko")
	float RotationSpeed = 30.0f;

};
