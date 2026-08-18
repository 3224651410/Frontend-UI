

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StoryPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API AStoryPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
