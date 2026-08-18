


#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "FrontendSettings/FrontendGameUserSettings.h"

FOptionsDataInteractionHelper::FOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath) : CachedDynamicFunctionPath(InSetterOrGetterFuncPath)
{
	CachedWeakGameUserSettings = UFrontendGameUserSettings::Get();
}

FString FOptionsDataInteractionHelper::GetValueAsString() const
{
	FString OutStringValue;
	PropertyPathHelpers::GetPropertyValueAsString(
		CachedWeakGameUserSettings.Get(),   //获取用户设置表
		CachedDynamicFunctionPath,          //利用哪个函数读取
		OutStringValue                      //从设置中读取到的值
	);

	return OutStringValue;
}

void FOptionsDataInteractionHelper::SetValueFromString(const FString& InStringValue)
{
	PropertyPathHelpers::SetPropertyValueFromString(   
		CachedWeakGameUserSettings.Get(),   //获取用户设置表
		CachedDynamicFunctionPath,          //利用哪个函数进行设置
		InStringValue                       //需要设置的值
	);
}