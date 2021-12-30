#include "ActionDataDetail.h"

#include "ActionData.h"
#include "DetailLayoutBuilder.h"

TSharedRef<IDetailCustomization> ActionDataDetail::MakeInstance()
{
	return MakeShareable(new ActionDataDetail());
}

void ActionDataDetail::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> CustomizedObjects;
	DetailBuilder.GetObjectsBeingCustomized(CustomizedObjects);

	Target = nullptr;
	for (TWeakObjectPtr<UObject> uObj : CustomizedObjects)
	{
		if (!uObj.IsValid())
			continue;;

		Target = Cast<UActionData>(uObj);
		if (Target)
			break;
	}

	if (Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("##### Target is here!! #####"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("##### Target is here!! #####"));
	}

	TSharedRef<IPropertyHandle> prop_actionType = DetailBuilder.GetProperty("actionType");
	TSharedRef<IPropertyHandle> prop_Length = DetailBuilder.GetProperty("fLength");
	TSharedRef<IPropertyHandle> prop_IsLoop = DetailBuilder.GetProperty("bIsLoop");

	auto& propLow_ActionType = DetailBuilder.AddPropertyToCategory(prop_actionType);
	auto& propLow_Length = DetailBuilder.AddPropertyToCategory(prop_Length);
	auto& propLow_IsLoop = DetailBuilder.AddPropertyToCategory(prop_IsLoop);

	// DetailBuilder.HideCategory("Action Event Data");
}