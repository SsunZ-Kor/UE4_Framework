#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "IDetailCustomization.h"
#include "SlateBasics.h"

class UActionData;
class CLIENT_API ActionDataDetail : public IDetailCustomization
{
public:
	const FString DefaultPath = TEXT("/Game");

private:
	UActionData* Target = nullptr;

public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	//FReply OnSaveAssetPathBtnClicked();
	//
	//EAppReturnType::Type CreatePickAssetPathWidget(FString& assetPath);
};
