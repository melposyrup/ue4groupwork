// Fill out your copyright notice in the Description page of Project Settings.


#include "NekoCharacter.h"
//Debug デバッグ
#include "DebugHelper.h"
//basic components 基本コンポーネント
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
//UI
#include "NekoPlayerController.h"
#include "NekoHUD.h"
#include "NekoOverlay.h"
#include "NekoMapUIComponent.h"
//Interact
#include "NekoComponentInteract.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
//launch
#include "Components/ArrowComponent.h"


// Sets default values
ANekoCharacter::ANekoCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(20.f, 20.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.4f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->JumpZVelocity = 1600.f;
	GetCharacterMovement()->GravityScale = 3.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ViewCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InteractComponent = CreateDefaultSubobject<UNekoComponentInteract>(TEXT("InteractComponent"));

	LaunchArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	LaunchArrow->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void ANekoCharacter::BeginPlay()
{
	Super::BeginPlay();

	// initialize NekoOverlay
	OverlayInitialize();

	//create MapUI
	FVector PlayerLocation = GetActorLocation();
	FActorSpawnParameters SpawnParameters;
	if (MapUIClassBP) {
		MapUIInstanceBP = GetWorld()->SpawnActor<ANekoMapUIComponent>(
			MapUIClassBP, PlayerLocation, FRotator::ZeroRotator, SpawnParameters);
	}

	//create MiniMapUI
	if (MiniMapUIClassBP) {
		MiniMapUIInstanceBP = GetWorld()->SpawnActor<ANekoMapUIComponent>(
			MiniMapUIClassBP, PlayerLocation, FRotator::ZeroRotator, SpawnParameters);
	}

	//hide launch arrow
	LaunchArrow->SetVisibility(false);

}
// Called every frame
void ANekoCharacter::Tick(float DeltaTime)
{
	//!bCanEverTick = true
	Super::Tick(DeltaTime);


	//update MiniMapUIInstance's transform
	{
		//update location, snap to player
		if (MiniMapUIInstanceBP) {
			MiniMapUIInstanceBP->SetActorLocation(GetActorLocation());
		}

		//rotate rotation on Z-axis, same with player
		if (MiniMapUIInstanceBP) {
			FRotator PlayerRotation = GetActorRotation();
			FRotator NewRotation(0.0f, PlayerRotation.Yaw, 0.0f); //FRotator( Y, Z, X ) pitch, yaw, roll
			MiniMapUIInstanceBP->SetActorRotation(NewRotation);
		}

	}

	//update arrow's rotation
	{
		//if arrow is visible
		if (LaunchArrow->IsVisible()) {
			FRotator ArrowRotation = UpdateLaunchArrowRotation();
			LaunchArrow->SetWorldRotation(ArrowRotation);
		}
	}
}

// Called to bind functionality to input
void ANekoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Launch", IE_Pressed, this, &ANekoCharacter::LaunchReady);
	PlayerInputComponent->BindAction("Launch", IE_Released, this, &ANekoCharacter::Launch);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ANekoCharacter::Interact);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ANekoCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ANekoCharacter::StopSprint);

	PlayerInputComponent->BindAction("Map", IE_Pressed, this, &ANekoCharacter::ShowMap);
	PlayerInputComponent->BindAction("Map", IE_Released, this, &ANekoCharacter::HideMap);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANekoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANekoCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ANekoCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ANekoCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ANekoCharacter::Sprint()
{
	if (GetCharacterMovement())
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

	Overlay->SetVisibilitySprintKey(false);

	PlaySound(SprintSound);
}

void ANekoCharacter::StopSprint()
{
	if (GetCharacterMovement())
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	Overlay->SetVisibilitySprintKey(true);
}

void ANekoCharacter::OverlayInitialize()
{
	// find controller -> find hud -> find overlay -> set overlay
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	ANekoHUD* NekoHUD = Cast<ANekoHUD>(PlayerController->GetHUD());
	if (!NekoHUD) return;

	Overlay = NekoHUD->GetNekoOverlay();
	if (!Overlay) return;

	Overlay->UpdateLaunchCount(LaunchItemCount);
}

void ANekoCharacter::ShowMap()
{
	if (!MapUIInstanceBP) return;

	//move MapUIInstance to the player's location
	FVector NewLocation = GetActorLocation();
	MapUIInstanceBP->SetActorLocation(NewLocation);

	//set MapUI to visible in overlay
	Overlay->SetVisibilityMapAndQuest(true);
	Overlay->SetVisibilityMapKey(false);
}

void ANekoCharacter::HideMap()
{
	if (!MapUIInstanceBP) return;

	//set MapUI to collaps in overlay
	Overlay->SetVisibilityMapAndQuest(false);
	Overlay->SetVisibilityMapKey(true);
}

void ANekoCharacter::Interact()
{
	if (!InteractComponent) return;

	//get ObjectiveID feedback from InteractComponent
	FString ObjectiveID = InteractComponent->Interact();
	//broadcast by player, listen by BP_QuestBase
	OnObjectiveIDCalled.Broadcast(ObjectiveID);
	Debug::PrintFixedLine("Interact: " + ObjectiveID, 12);

	PlaySound(InteractSound);
}

void ANekoCharacter::PlaySound(USoundBase* Sound)
{
	if (!Sound) return;
	AudioComponent = UGameplayStatics::SpawnSoundAttached(
		Sound,
		GetRootComponent(),
		NAME_None,
		GetActorLocation(),
		EAttachLocation::KeepRelativeOffset
	);

	if (!AudioComponent) return;

	AudioComponent->Play(0.f);
}

void ANekoCharacter::LaunchReady()
{
	//check if LaunchItemCount > 0, can launch
	if (!(LaunchItemCount > 0)) {
		PlaySound(LaunchFailedSound);
		return;
	}
	PlaySound(LaunchReadySound);

	//show arrow, update arrow's rotation in tick
	LaunchArrow->SetVisibility(true);

}

void ANekoCharacter::Launch()
{
	//if arrow is invisible, return
	if (!LaunchArrow->IsVisible()) return;

	//TODO play launch animation effect

	//play launch sound
	PlaySound(LaunchSound);

	//launch character in the direction of arrow
	{
		FVector ArrowRotation = UpdateLaunchArrowRotation().Vector();
		GetCharacterMovement()->Launch(ArrowRotation * JumpPadForce);
	}

	//rotate player to arrow direction
	{
		FRotator ArrowRotation = UpdateLaunchArrowRotation();
		ArrowRotation.Pitch = 0;
		SetActorRotation(ArrowRotation);
	}

	//hide arrow
	LaunchArrow->SetVisibility(false);

	//LaunchItemCount--, update LaunchItemCount in overlay
	LaunchItemCount--;
	Overlay->UpdateLaunchCount(LaunchItemCount);
}

FRotator ANekoCharacter::UpdateLaunchArrowRotation()
{
	FRotator CameraRotation = ViewCamera->GetComponentRotation();

	// GetReflectionVector of CameraRotation based on gound
	// and keep it above horizon
	float Pitch = FMath::Clamp(-CameraRotation.Pitch, 10.f, 89.0f);
	CameraRotation.Pitch = Pitch;
	FRotator ArrowRotation = 
		FRotator(Pitch, CameraRotation.Yaw, CameraRotation.Roll);

	return ArrowRotation;
}


void ANekoCharacter::OnJumpPad(FVector LaunchDirection)
{
	//JumpPad is facing to sky as default value
	GetCharacterMovement()->Launch(LaunchDirection * JumpPadForce);
	PlaySound(LaunchSound);
}

void ANekoCharacter::LaunchItemCountIncrease(int32 value)
{
	LaunchItemCount += value;
	Overlay->UpdateLaunchCount(LaunchItemCount);
}
