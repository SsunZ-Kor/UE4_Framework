// Fill out your copyright notice in the Description page of Project Settings.
#include "ActionEventDataBase.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "EditorWidgets/Public/SEnumCombobox.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Input/SRotatorInputBox.h"
#endif

FActionEventDataBase::FActionEventDataBase()
{
	fStartTime = 0.f;

#if WITH_EDITOR
	m_bIsFolded_EditorContentsWidget = false;
#endif
}

FActionEventDataBase::~FActionEventDataBase()
{
}

CreateRuntimeResult FActionEventDataBase::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	CreateRuntimeResult result;

	result.pUObject = nullptr;
	result.pRuntime = nullptr;

	return result;
}

EActionEventTypes FActionEventDataBase::GetActionEventType() const
{
	return EActionEventTypes::None;
}

FString FActionEventDataBase::GetActionEventName() const
{
	return UEnumToString(GetActionEventType());
}

bool FActionEventDataBase::IsDuration() const
{
	return false;
}

#if WITH_EDITOR
const float FActionEventDataBase::MAX_LABEL_WIDTH = 150.f;

TSharedRef<SWidget> FActionEventDataBase::GetEditorTimeWidget(UActionData* pActionData)
{
	return SNew(SHorizontalBox)
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
		.WidthOverride(MAX_LABEL_WIDTH * 0.5f)
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
	];
}

TSharedRef<SWidget> FActionEventDataBase::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(STextBlock)
	.Text(FText::FromString(TEXT("Abstract")));
}

const bool& FActionEventDataBase::GetFolded_EditorContentsWidget()
{
	return m_bIsFolded_EditorContentsWidget;
}

void FActionEventDataBase::SetFolded_EditorContentsWidget(const bool& bFolded)
{
	m_bIsFolded_EditorContentsWidget = bFolded;
}

void FActionEventDataBase::AdjustEditorData()
{
}

TSharedRef<SWidget> FActionEventDataBase::EditorInt(FString fieldName, int& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SNumericEntryBox<int>)
		.Value_Lambda([&val]()
		{
			return val;
		})
		.OnValueChanged_Lambda([&val, pActionData](int intValue)
		{
			if (val != intValue)
			{
				val = intValue;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorInt(FString fieldName, int& val, const int& min, const int& max, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SNumericEntryBox<int>)
		.MinValue(min)
		.MaxValue(max)
		.Value_Lambda([&val]()
		{
			return val;
		})
		.OnValueChanged_Lambda([&val, pActionData](int intValue)
		{
			if (val != intValue)
			{
				val = intValue;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorFloat(FString fieldName, float& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SNumericEntryBox<float>)
		.Value_Lambda([&val]()
		{
			return val;
		})
		.OnValueChanged_Lambda([&val, pActionData](float floatValue)
		{
			
			if (val != floatValue)
			{
				val = floatValue;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorFloat(FString fieldName, float& val, const float& min, const float& max, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SNumericEntryBox<float>)
		.MinValue(min)
		.MaxValue(max)
		.Value_Lambda([&val]()
		{
			return val;
		})
		.OnValueChanged_Lambda([&val, pActionData](float floatValue)
		{
			if (val != floatValue)
			{
				val = floatValue;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorVector(FString fieldName, FVector& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SVectorInputBox)
		.X_Lambda([&val](){return val.X;})
		.Y_Lambda([&val](){return val.Y;})
		.Z_Lambda([&val](){return val.Z;})
		.OnXChanged_Lambda([&val, pActionData](float x)
		{
			if (val.X != x)
			{
				val.X = x;
				pActionData->MakeDirty();
			}
		})
		.OnYChanged_Lambda([&val, pActionData](float y)
		{
			if (val.Y != y)
			{
				val.Y = y;
				pActionData->MakeDirty();
			}
		})
		.OnZChanged_Lambda([&val, pActionData](float z)
		{
			if (val.Z != z)
			{
				val.Z = z;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorRotator(FString fieldName, FRotator& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SRotatorInputBox)
		.Yaw_Lambda([&val](){return val.Yaw;})
		.Pitch_Lambda([&val](){return val.Pitch;})
		.Roll_Lambda([&val](){return val.Roll;})
		.OnYawChanged_Lambda([&val, pActionData](float y)
		{
			if (val.Yaw != y)
			{
				val.Yaw = y;
				pActionData->MakeDirty();
			}
		})
		.OnPitchChanged_Lambda([&val, pActionData](float p)
		{
			if (val.Pitch != p)
			{
				val.Pitch = p;
				pActionData->MakeDirty();
			}
		})
		.OnRollChanged_Lambda([&val, pActionData](float r)
		{
			if (val.Roll != r)
			{
				val.Roll = r;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorQuat(FString fieldName, FQuat& val, UActionData* pActionData)
{
	
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SRotatorInputBox)
		.Yaw_Lambda([&val](){return val.Rotator().Yaw;})
		.Pitch_Lambda([&val](){return val.Rotator().Pitch;})
		.Roll_Lambda([&val](){return val.Rotator().Roll;})
		.OnYawChanged_Lambda([&val, pActionData](float y)
		{
			auto rot = val.Rotator();
			if (rot.Yaw != y)
			{
				rot.Yaw = y;
				val = rot.Quaternion();
				pActionData->MakeDirty();
			}
		})
		.OnPitchChanged_Lambda([&val, pActionData](float p)
		{
			auto rot = val.Rotator();
			if (rot.Pitch != p)
			{
				rot.Pitch = p;
				val = rot.Quaternion();
				pActionData->MakeDirty();
			}
		})
		.OnRollChanged_Lambda([&val, pActionData](float r)
		{
			auto rot = val.Rotator();
			if (rot.Roll != r)
			{
				rot.Roll = r;
				val = rot.Quaternion();
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorName(FString fieldName, FName& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SEditableTextBox)
		.Text(FText::FromName(val))
		.OnTextChanged_Lambda([&val, pActionData](FText text)
		{
			auto newVal = FName(*text.ToString());
			if (val != newVal)
			{
				val = newVal;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorText(FString fieldName, FText& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SEditableTextBox)
		.Text(val)
		.OnTextChanged_Lambda([&val, pActionData](FText text)
		{
			if (val.CompareTo(text))
			{
				val = text;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorString(FString fieldName, FString& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SEditableTextBox)
		.Text(FText::FromString(val))
		.OnTextChanged_Lambda([&val, pActionData](FText text)
		{
			auto newVal = text.ToString();
			if (val != newVal)
			{
				val = newVal;
				pActionData->MakeDirty();
			}
		})
	];
}

TSharedRef<SWidget> FActionEventDataBase::EditorBool(FString fieldName, bool& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SCheckBox)
		.IsChecked_Lambda([&val]()
		{
			return val ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		})
		.OnCheckStateChanged_Lambda([&val, pActionData](ECheckBoxState state)
		{
			auto newVal = false;
			switch (state)
			{
				case ECheckBoxState::Checked :	newVal = true;	break;
				default:										break;
			}

			if (val != newVal)
			{
				val = newVal;
				pActionData->MakeDirty();
			}
		})
	];
}

template <typename T>
TSharedRef<SWidget> FActionEventDataBase::EditorEnum(FString fieldName, T& val, UActionData* pActionData)
{
	return SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(2.5f, 2.5f, 1.25f, 2.5f)
	[
		SNew(SBox)
		.WidthOverride(MAX_LABEL_WIDTH)
		.VAlign(EVerticalAlignment::VAlign_Center)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(fieldName))
		]
	]
	+SHorizontalBox::Slot()
	.Padding(1.25f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SEnumComboBox, StaticEnum<T>())
		.CurrentValue_Lambda([&val]()
		{
			return static_cast<int32>(val);
		})
		.OnEnumSelectionChanged_Lambda([&val, pActionData](int32 enumValue, ESelectInfo::Type selectInfoType)
		{
			auto newVal = static_cast<T>(enumValue);
			if (val != newVal)
			{
				val = newVal;
				pActionData->MakeDirty();
			}
		})
	];
}

template <typename T>
TSharedRef<SWidget> FActionEventDataBase::EditorList(
	FString fieldName,
	TArray<T>& item,
	bool& bIsFolded,
	typename SListView<T>::FOnGenerateRow onGenerateRow,
	typename SListView<T>::FOnSelectionChanged onSelectionChenged,
	FOnClicked onClicked_Create,
	UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.5f, 2.5f, 1.25f, 2.5f)
		[
			SNew(SBox)
			.WidthOverride(MAX_LABEL_WIDTH)
			.VAlign(EVerticalAlignment::VAlign_Center)
			.HAlign(EHorizontalAlignment::HAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(fieldName))
			]
		]
		+SHorizontalBox::Slot().AutoWidth()
		.Padding(1.25f, 2.5f, 2.5f, 1.25f)
		[
			SNew(SButton)
			.Text_Lambda([&bIsFolded]()
			{
				if (bIsFolded)
					return FText::FromString(TEXT("▼"));
				else
					return FText::FromString(TEXT("▲"));
			})
			.OnClicked_Lambda([&bIsFolded]()
			{
				bIsFolded = !bIsFolded;
				return FReply::Handled();
			})
		]
		+SHorizontalBox::Slot()
		+SHorizontalBox::Slot().AutoWidth()
		.Padding(1.25f, 2.5f, 2.5f, 2.5f)
		[
			SNew(SButton)
			.ForegroundColor(FColor::White)
			.ButtonColorAndOpacity(FColor(0, 180, 0, 255))
			.Text(FText::FromString(TEXT("+")))
			.OnClicked_Lambda([onClicked_Create, pActionData]()
			{
				if (onClicked_Create.IsBound())
				{
					onClicked_Create.Execute();
					pActionData->MakeDirty();
				}

				return FReply::Handled();
			})
		]
	]
	+SVerticalBox::Slot().AutoHeight().Padding(50.f, 2.5f, 2.5f, 2.5f)
	[
		SNew(SListView<T>)
		.Visibility_Lambda([&bIsFolded](){return bIsFolded ? EVisibility::Collapsed : EVisibility::Visible;})
		.ItemHeight(24)
		.ListItemsSource(&item)
		.OnGenerateRow        (onGenerateRow)
		.OnSelectionChanged   (onSelectionChenged)
	];
}

#endif
