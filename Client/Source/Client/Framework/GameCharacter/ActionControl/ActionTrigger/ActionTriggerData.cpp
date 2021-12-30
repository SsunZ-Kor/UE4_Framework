#include "ActionTriggerData.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#include "Widgets/Input/SNumericEntryBox.h"
#endif

FActionTriggerData::FActionTriggerData()
{
	AreaType = ETriggerAreaTypes::Ground;
	AxisType = ETriggerAxisTypes::None;
	EventType = ETriggerEventTypes::None;

	fStartTime = 0.f;
	fEndTime = 99999.f;
}

FActionTriggerData::~FActionTriggerData()
{
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionTriggerData::GetEditorTimeWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.5f)
		[
			SNew(SBox)
			.WidthOverride(FActionEventDataBase::MAX_LABEL_WIDTH)
			.VAlign(EVerticalAlignment::VAlign_Center)
			.HAlign(EHorizontalAlignment::HAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Start Time")))
			]
		]
		+SHorizontalBox::Slot()
		.Padding(2.5f)
		[
			SNew(SSlider)
			.MinValue(0.f)
			.MaxValue(pActionData->fLength)
			.Value_Lambda([this](){return fStartTime;})
			.OnValueChanged_Lambda([this, pActionData](float v)
			{
				if (fStartTime != v)
				{
					fStartTime = v;
					pActionData->MakeDirty();
				}
			})
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.5f)
		[
			SNew(SBox)
			.WidthOverride(FActionEventDataBase::MAX_LABEL_WIDTH * 0.5f)
			[
				SNew(SNumericEntryBox<float>)
				.MinValue(0.f)
				.MaxValue(pActionData->fLength)
				.Value_Lambda([this](){return fStartTime;})
				.OnValueChanged_Lambda([this, pActionData](float v)
				{
					if (fStartTime != v)
					{
						fStartTime = v;
						pActionData->MakeDirty();
					}
				})
			]
		]
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.5f)
		[
			SNew(SBox)
			.WidthOverride(FActionEventDataBase::MAX_LABEL_WIDTH)
			.VAlign(EVerticalAlignment::VAlign_Center)
			.HAlign(EHorizontalAlignment::HAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("End Time")))
			]
		]
		+SHorizontalBox::Slot()
		.Padding(2.5f)
		[
			SNew(SSlider)
			.MinValue(0.f)
			.MaxValue(pActionData->fLength)
			.Value_Lambda([this](){return fEndTime;})
			.OnValueChanged_Lambda([this, pActionData](float v)
			{
				if (fEndTime != v)
				{
					fEndTime = v;
					pActionData->MakeDirty();
				}
			})
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.5f)
		[
			SNew(SBox)
			.WidthOverride(FActionEventDataBase::MAX_LABEL_WIDTH * 0.5f)
			[
				SNew(SNumericEntryBox<float>)
				.MinValue(0.f)
				.MaxValue(pActionData->fLength)
				.Value_Lambda([this](){return fEndTime;})
				.OnValueChanged_Lambda([this, pActionData](float v)
				{
					if (fEndTime != v)
					{
						fEndTime = v;
						pActionData->MakeDirty();
					}
				})
			]
		]
	];
}

TSharedRef<SWidget> FActionTriggerData::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				FActionEventDataBase::EditorString(TEXT("ActionName"), NextActionName, pActionData)
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				FActionEventDataBase::EditorEnum(TEXT("AreaType"), AreaType, pActionData)
			]
		]
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				FActionEventDataBase::EditorEnum(TEXT("AxisType"), AxisType, pActionData)
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				FActionEventDataBase::EditorEnum(TEXT("EventType"), EventType, pActionData)
			]
		]
		+SHorizontalBox::Slot()
	];
}

const bool& FActionTriggerData::GetFolded_EditorContentsWidget()
{
	return m_bIsFolded_EditorContentsWidget;
}

void FActionTriggerData::SetFolded_EditorContentsWidget(const bool& bFolded)
{
	m_bIsFolded_EditorContentsWidget = bFolded;
}
#endif