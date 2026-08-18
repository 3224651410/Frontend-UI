#pragma once

#include "CoreMinimal.h"
#include "Characters/ProjectCharacter.h"
#include "StoryCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class FRONTENDUI_API AStoryCharacter : public AProjectCharacter
{
	GENERATED_BODY()

public:
	AStoryCharacter();

	//~ Begin Character Interface 
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//~ End Character Interface 

protected:
	/** Third-person camera boom */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	/** Placeholder visible body (engine cube; swap with a real character mesh later) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
	TObjectPtr<UStaticMeshComponent> BodyMesh;	

	/** Overall look sensitivity multiplier (raw mouse sensitivity is pre-scaled by mapping modifiers) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "0.0"))
	float LookSensitivity = 1.0f;

	//~ Input callbacks
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();
	//~ End Input callbacks

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

};
