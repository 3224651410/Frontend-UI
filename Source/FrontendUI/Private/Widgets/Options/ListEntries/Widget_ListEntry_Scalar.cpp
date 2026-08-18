


#include "Widgets/Options/ListEntries/Widget_ListEntry_Scalar.h"
#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"
#include "AnalogSlider.h"

void UWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AnalogSlider_SettingSlider->OnValueChanged.AddUniqueDynamic(this, &ThisClass::OnSliderValueChanged);
	AnalogSlider_SettingSlider->OnMouseCaptureBegin.AddUniqueDynamic(this, &ThisClass::OnSliderMouseCaptureBegin);
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningSclarDataObject = CastChecked<UListDataObject_Scalar>(InOwningListDataObject);

	CommonNumeric_SettingValue->SetNumericType(CachedOwningSclarDataObject->GetDisplayNumericType());
	CommonNumeric_SettingValue->FormattingSpecification = CachedOwningSclarDataObject->GetNumberFormattingOptions();
	CommonNumeric_SettingValue->SetCurrentValue(CachedOwningSclarDataObject->GetCurrentValue());

	AnalogSlider_SettingSlider->SetMinValue(CachedOwningSclarDataObject->GetDisplayValueRange().GetLowerBoundValue());
	AnalogSlider_SettingSlider->SetMaxValue(CachedOwningSclarDataObject->GetDisplayValueRange().GetUpperBoundValue());
	AnalogSlider_SettingSlider->SetStepSize(CachedOwningSclarDataObject->GetSliderStepSize());
	AnalogSlider_SettingSlider->SetValue(CachedOwningSclarDataObject->GetCurrentValue());
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (CachedOwningSclarDataObject)
	{
		CommonNumeric_SettingValue->SetCurrentValue(CachedOwningSclarDataObject->GetCurrentValue());
		AnalogSlider_SettingSlider->SetValue(CachedOwningSclarDataObject->GetCurrentValue());
	}
}

void UWidget_ListEntry_Scalar::OnSliderValueChanged(float Value)
{
	if (CachedOwningSclarDataObject)
	{
		CachedOwningSclarDataObject->SetCurrentValueFromSlider(Value);
	}
}

void UWidget_ListEntry_Scalar::OnSliderMouseCaptureBegin()
{
	SelectThisEntryWidget();

}
