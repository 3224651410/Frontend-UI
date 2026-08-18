#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontendPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API AFrontendPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	//~Begin PlayerController Interface
	virtual void OnPossess(APawn* aPawn) override;
	//~End PlayerController Interface
};
