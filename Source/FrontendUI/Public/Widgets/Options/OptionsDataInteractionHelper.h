

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class UFrontendGameUserSettings;
/**
 * 
 */
class FRONTENDUI_API FOptionsDataInteractionHelper
{
public:
	FOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath); //输入所需要用到的函数的名字

	FString GetValueAsString() const;
	void SetValueFromString(const FString& InStringValue);


private:

	FCachedPropertyPath CachedDynamicFunctionPath;

	TWeakObjectPtr<UFrontendGameUserSettings> CachedWeakGameUserSettings;
};
