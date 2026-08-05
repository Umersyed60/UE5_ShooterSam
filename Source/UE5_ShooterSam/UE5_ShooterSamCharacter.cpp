// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_ShooterSamCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "UE5_ShooterSam.h"
#include "UE5_ShooterSamPlayerController.h"

AUE5_ShooterSamCharacter::AUE5_ShooterSamCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AUE5_ShooterSamCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	//Update Health Bar
	UpdateHUD();

	//Assigning Damage function to Delegate
	OnTakeAnyDamage.AddDynamic(this, &AUE5_ShooterSamCharacter::OnDamageTaken);

	//Hiding Old Weapon in Sekeletal Mesh
	GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);

	//Spawning Gun Actor, Setting Owner, and Attaching to a Weapon Socket
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	if (Gun) {
		Gun->SetOwner(this);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->OwnerController = GetController();
	}
}

void AUE5_ShooterSamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUE5_ShooterSamCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AUE5_ShooterSamCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUE5_ShooterSamCharacter::Look);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AUE5_ShooterSamCharacter::Shoot);
	}
	else
	{
		UE_LOG(LogUE5_ShooterSam, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AUE5_ShooterSamCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AUE5_ShooterSamCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AUE5_ShooterSamCharacter::Shoot()
{
	//Shooting Gun
	if (Gun) {
		Gun->PullTrigger();
	}
}

void AUE5_ShooterSamCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AUE5_ShooterSamCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AUE5_ShooterSamCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AUE5_ShooterSamCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AUE5_ShooterSamCharacter::UpdateHUD()
{
	AUE5_ShooterSamPlayerController* PlayerController = Cast<AUE5_ShooterSamPlayerController>(GetController());
	if (PlayerController) {
		float NewPercent = Health / MaxHealth;

		if (NewPercent < 0.0f) {
			NewPercent = 0.0f;
		}

		PlayerController->HUDWidget->SetHealthBarPercent(NewPercent);
	}
}

void AUE5_ShooterSamCharacter::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//If Is Alive Apply Damage
	if (IsAlive) {
		Health -= Damage;

		//Update Health Bar
		UpdateHUD();

		//If Health Is Less Than Zero Case
		if (Health <= 0.0f) {
			Health = 0.0f;
			IsAlive = false;

			//Disable Capsule Component On Zero Health
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			//Diables Player Input
			DetachFromControllerPendingDestroy();
		}
	}
}
