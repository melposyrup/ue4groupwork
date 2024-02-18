// Fill out your copyright notice in the Description page of Project Settings.


#include "NekoCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
//#include "PaperSpriteComponent.h"
//#include "Components/SceneCaptureComponent2D.h"
#include "DebugHelper.h"
#include "NekoOverlay.h"
#include "NekoHUD.h"


// Sets default values
ANekoCharacter::ANekoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(20.f, 20.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ViewCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// minimap components
	//MinimapCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MinimapCameraBoom"));
	//MinimapCameraBoom->SetupAttachment(RootComponent);
	//MinimapCameraBoom->TargetArmLength = 1000.0f;
	//MinimapCameraBoom->bUsePawnControlRotation = false;
	//MinimapCameraBoom->SetRelativeRotation(FRotator(270.f, 0.f, 0.f));

	//MinimapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MinimapCamera"));
	//MinimapCamera->SetupAttachment(MinimapCameraBoom, USpringArmComponent::SocketName);
	//MinimapCamera->ProjectionType = ECameraProjectionMode::Type::Orthographic;

	//PlayerIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayerIcon"));
	//PlayerIcon->SetupAttachment(RootComponent);
}


void ANekoCharacter::BeginPlay()
{
	Super::BeginPlay();

	OverlayInit();
}


void ANekoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//todo: update Sprint Stamina
}

#pragma region Input 

void ANekoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ANekoCharacter::Sprint);
	//PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ANekoCharacter::StopSprint);

	//PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ANekoCharacter::Interact);

	PlayerInputComponent->BindAction("Map", IE_Pressed, this, &ANekoCharacter::MapOverlayOnOff);


	PlayerInputComponent->BindAxis("MoveForward", this, &ANekoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANekoCharacter::MoveRight);

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


#pragma endregion 

#pragma region UI and Overlay

void ANekoCharacter::OverlayInit()
{
	// find controller -> find hud -> find overlay -> set overlay
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	ANekoHUD* NekoHUD = Cast<ANekoHUD>(PlayerController->GetHUD());
	if (!NekoHUD) return;

	Overlay = NekoHUD->GetNekoOverlay();
	if (!Overlay) return;

	Overlay->ShowCanvus(Overlay->GetMap(), false);

	// todo set currency, stamina, sense to zero
}

void ANekoCharacter::MapOverlayOnOff()
{
	if (!Overlay) return;

	bool visible = Overlay->IsCanvusVisible(Overlay->GetMap());

	if (visible)
	{
		Overlay->DeleteQuestWidget();
	}
	else
	{
		Overlay->CreateQuestWidget();
	}
	Overlay->ShowCanvus(Overlay->GetMap(), !visible);
	Overlay->ShowMapTutorialBox(visible);
}

#pragma endregion 