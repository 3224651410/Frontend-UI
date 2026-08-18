

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FrontendTypes/FrontendEnumTypes.h"

#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;
class UListDataObject_Base;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);
	void NativeOnListEntryWidgetHovered(bool bWasHovered);

	//~ Begin UUserWidget Interface
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	//~ End UUserWidget Interface

protected:
	// 子类重写此函数让手柄交互
	UFUNCTION(BlueprintImplementableEvent, meta = (DispalayName = "Get Widget To Focus For Gamepad"))
	UWidget* BP_GetWidgetToFocusForGamepad() const;

	// 子类控件蓝图重写此函数来实现当控件被悬停或选中时是否高亮
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Toggle Entry Widget High light State"))
	void BP_OnToggleEntryWidgetHighlightState(bool bShouldHighlight) const;

	//~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnEntryReleased() override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	//~ End IUserObjectListEntry Interface

	//子类应该重写此函数以处理所需的初始化，应先使用Super
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject);

	//子类应该重写此函数，使得在数据对象被修改后更新UI显示，不用Super
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason);

	virtual void OnOwningDependencyDataObjectModified(UListDataObject_Base* OwningModifiedDependencyData, EOptionsListDataModifyReason ModifyReason);

	//子类应重写此函数，以管理控件的可编辑状态，需调用Super
	virtual void OnToggleEditableState(bool bIsEditable);

	void SelectThisEntryWidget();

private:
	//***** Bound Widgets ***** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional,AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;
	//***** Bound Widgets ***** //

	UPROPERTY(Transient)
	UListDataObject_Base* CachedOwningDataObject;
};
