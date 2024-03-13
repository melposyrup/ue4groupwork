
#include "NekoComponentInteract.h"
#include "NekoCharacter.h"
#include "NekoInterfaceInteract.h"
#include "DebugHelper.h"

// Sets default values for this component's properties
UNekoComponentInteract::UNekoComponentInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Owner = Cast<ANekoCharacter>(GetOwner());
}

// Called when the game starts
void UNekoComponentInteract::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UNekoComponentInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FString UNekoComponentInteract::Interact()
{
	AActor* HitActor = Raycast().GetActor();

	FString ObjectiveID = "None";

	//if (!HitActor) ObjectiveID = "HitActor null";

	if (HitActor && HitActor->Implements<UNekoInterfaceInteract>())
	{
		ObjectiveID = INekoInterfaceInteract::Execute_Interact(HitActor);
		//Debug::Print(ObjectiveID);
	}
	return ObjectiveID;
}

FHitResult UNekoComponentInteract::Raycast()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); //to interact with Jumppad
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn); //to interact with NPC

	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 800.f);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, End, ObjectQueryParams);

	DRAW_LINE(EyeLocation, End);

	return HitResult;
}
