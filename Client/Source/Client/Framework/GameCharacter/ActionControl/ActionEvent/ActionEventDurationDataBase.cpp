// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventDurationDataBase.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#include "Widgets/Input/SNumericEntryBox.h"
#endif

FActionEventDurationDataBase::FActionEventDurationDataBase()
{
}

FActionEventDurationDataBase::~FActionEventDurationDataBase()
{
}

bool FActionEventDurationDataBase::IsDuration() const
{
	return true;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventDurationDataBase::GetEditorTimeWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		FActionEventDataBase::GetEditorTimeWidget(pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.5f)
		[
			SNew(SBox)
			.WidthOverride(MAX_LABEL_WIDTH)
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
			.MinValue(fStartTime)
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
			.WidthOverride(MAX_LABEL_WIDTH)
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
#endif