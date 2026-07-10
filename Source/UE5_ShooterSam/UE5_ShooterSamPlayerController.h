// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "HUDWidget.h"

#include "UE5_ShooterSamPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class AUE5_ShooterSamPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

public:
	// Exposes a dropdown in Blueprints to assign your specific Widget Blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	// Stores the runtime instance of the created widget to prevent garbage collection
	UPROPERTY(VisibleAnywhere)
	UHUDWidget* HUDWidget;
};
