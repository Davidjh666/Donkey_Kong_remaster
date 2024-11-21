// Copyright Epic Games, Inc. All Rights Reserved.

#include "Donkey_kong_remasterCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "proyectil.h"

ADonkey_kong_remasterCharacter::ADonkey_kong_remasterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ADonkey_kong_remasterCharacter::Disparar()
{
	FVector ubicacion = GetActorLocation() + FVector(20.0f, 0.0f, 20.0f);
	//FVector ubicacion1 = GetActorLocation() + FVector(0.0f, 0.0f, 55.0f);
	FRotator rotacion = GetActorRotation();
	Aproyectil* NewProj0 = GetWorld()->SpawnActor<Aproyectil>(ubicacion, rotacion);
	//AProyectil* NewProj1 = GetWorld()->SpawnActor<AProyectil>(ubicacion1, rotacion);
}

void ADonkey_kong_remasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	//// Create a proyectil
	//ACharacter* Mario = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//if (Mario) {
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
	//		FString::Printf(TEXT("Mario encontrado")));
	//}

	

}

void ADonkey_kong_remasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	proyectilRecord += 1;
	if (proyectilRecord >= 50)
	{
		//Disparar();
		proyectilRecord = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADonkey_kong_remasterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADonkey_kong_remasterCharacter::MoveRight);
	PlayerInputComponent->BindAction("Disparar", IE_Pressed, this, &ADonkey_kong_remasterCharacter::Disparar);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADonkey_kong_remasterCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADonkey_kong_remasterCharacter::TouchStopped);
}

void ADonkey_kong_remasterCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ADonkey_kong_remasterCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ADonkey_kong_remasterCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

