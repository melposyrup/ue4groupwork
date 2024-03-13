// ==================================================
// Filename	:	NekoJumppad.h
// Author	:	22cu0214 JinWener
// Description:	
// Notes		:	
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NekoInterfaceInteract.h"
#include "NekoJumppad.generated.h"

UCLASS()
class SHIRONEKOCPP_API ANekoJumppad : public AActor, public INekoInterfaceInteract
{
	GENERATED_BODY()

	//override
public:
	ANekoJumppad();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	//custom function
public:
	virtual FString Interact_Implementation() override;

protected:
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	//custom variable
	UPROPERTY(VisibleAnywhere, Category = "Shironeko")
	class UBoxComponent* BoxComponent; //for collision

	UPROPERTY(VisibleAnywhere, Category = "Shironeko")
	class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Shironeko")
	class USphereComponent* SphereComponent; //for overlap
};
