

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FrontendTypes/FrontendEnumTypes.h"
#include "FrontendTypes/FrontendStructTypes.h"

#include "ListDataObject_Base.generated.h"


#define LIST_DATA_ACCESSOR(DataType,PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName;} \
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName;}


/**
 * 
 */
UCLASS(Abstract)
class FRONTENDUI_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate, UListDataObject_Base*, EOptionsListDataModifyReason)
	FOnListDataModifiedDelegate OnListDataModified;
	FOnListDataModifiedDelegate OnDependencyDataModified;

	LIST_DATA_ACCESSOR(FName, DataID)
	LIST_DATA_ACCESSOR(FText, DataDisplayName)
	LIST_DATA_ACCESSOR(FText, DescriptionRichText)
	LIST_DATA_ACCESSOR(FText, DisabledRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData)

	void InitDataObject();

	// 在基类中为空。子类ListDataObject_Collection应重写该函数。该函数应返回标签页包含的所有子数据
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const { return TArray<UListDataObject_Base*>(); }
	
	virtual bool HasAnyChildListData() const { return false; }

	void SetShouldApplySettingsImmediately(bool bShouldApplyRightAway) { bShouldApplyChangeImmediatly = bShouldApplyRightAway; }

	//子类需重写这些函数以实现数据重置逻辑
	virtual bool HasDefaultValue() const { return false; }
	virtual bool CanResetBackToDafaultValue() const { return false; }
	virtual bool TryResetBackToDafalutValue() { return false; }

	//该函数会被注册表调用，来为构造好的ListDataObject添加编辑条件
	void AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition);

	//被数据表调用用来添加依赖数据
	void AddEditDependencyData(UListDataObject_Base* InDependencyData);
	
	bool IsDataCurrentlyEditable();


protected:
	// 基类中为空，派生类需要重写该函数，用来处理相应的初始化
	virtual void OnDataObjectInitialized();

	// 通知数据表更改
	virtual void NotifyListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified);

	//子类重写此函数以判断是否能设置强制值
	virtual bool CanSetToForcedStringValue(const FString& InForcedValue) const { return false; }

	//子类重写该函数以定义如何设置强制值
	virtual void OnSetToForcedStringValue(const FString& InForcedValue) {}

	//在依赖值被改变时被调用，子类可重写来实现自定义行为，需要调用Super::
	virtual void OnEditDependencyDataModified(UListDataObject_Base* ModifiedDependencyData, EOptionsListDataModifyReason ModifyReason);

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	UListDataObject_Base* ParentData;

	bool bShouldApplyChangeImmediatly = false;

	UPROPERTY(Transient)
	TArray<FOptionsDataEditConditionDescriptor> EditConditionDescArray;
};
