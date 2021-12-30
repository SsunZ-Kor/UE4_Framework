#include "Widget_ActionData.h"

#include "SEnumCombobox.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"

void Widget_ActionData::Construct(const FArguments& InArgs)
{
	tool = InArgs._Tool;
	if (!tool.IsValid())
		return;

	// 슬롯
	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.Padding(5.f)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Events")))
					.ButtonColorAndOpacity_Lambda([this](){return m_Mode == EWidgetActionDataMode::Event ? FColor::Orange : FColor::White;})
					.OnClicked_Lambda([this](){m_Mode = EWidgetActionDataMode::Event; return FReply::Handled();})
				]
				+SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Triggers")))
					.ButtonColorAndOpacity_Lambda([this](){return m_Mode == EWidgetActionDataMode::Trigger ? FColor::Orange : FColor::White;})
					.OnClicked_Lambda([this](){m_Mode = EWidgetActionDataMode::Trigger; return FReply::Handled();})
				]
			]
			// 이벤트 모드
			+SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				.Visibility_Lambda([this]()
				{
					if (tool.Pin()->GetSelectedActionData() && m_Mode == EWidgetActionDataMode::Event)
						return EVisibility::Visible;

					return EVisibility::Collapsed;
				})
				// 기본 데이터
				+ SHorizontalBox::Slot().Padding(5.f)
				[
					SNew(SScrollBox)
					+ SScrollBox::Slot()
					.VAlign(VAlign_Top)
					[
						SNew(SListView<TSharedPtr<FActionEventDataBase>>)
						.ItemHeight(24)
						.ListItemsSource(&tool.Pin()->GetSelectedActionEventData())
						.OnGenerateRow        (this, &Widget_ActionData::OnGenerateRowForActionEventDataList )
						.OnSelectionChanged   (this, &Widget_ActionData::OnSelectionChangedForActionEventDataList)
					]
				]
				// 이벤트 리스트
				+ SHorizontalBox::Slot().AutoWidth()
				[
					SNew(SBox)
					.WidthOverride(250)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().Padding(5.f).AutoHeight()
						[
							GetWidget_ActionBasicData()
						]
						+SVerticalBox::Slot().Padding(5.f)
						[
							SNew(SScrollBox)
							+ SScrollBox::Slot()
							.VAlign(VAlign_Top)
							[
								SNew(SListView<TSharedRef<EActionEventTypes>>)
								.ItemHeight(24)
								.ListItemsSource(&tool.Pin()->GetAllActionEventTypes())
								.OnGenerateRow_Lambda([this](TSharedRef<EActionEventTypes> InInfo,const TSharedRef<STableViewBase>& OwnerTable)
								{
									return SNew(STableRow<TSharedRef<EActionEventTypes>>, OwnerTable)
									.Padding(2.f)
									[
										SNew(SButton)
										.Text(FText::FromString(UActionData::GetEventName(InInfo.Get())))
										.OnClicked_Lambda([this, InInfo]()
										{
											tool.Pin()->GetSelectedActionEventData().Add(MakeShareable(UActionData::CreateActionEventForEditor(InInfo.Get())));
											tool.Pin()->GetSelectedActionData()->MakeDirty();
											return FReply::Handled();
										})
									];
								})
							]
						]
					]
				]
			]
			// 트리거 모드
			+SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				.Visibility_Lambda([this]()
				{
					if (tool.Pin()->GetSelectedActionData() && m_Mode == EWidgetActionDataMode::Trigger)
						return EVisibility::Visible;

					return EVisibility::Collapsed;
				})
				// 기본 데이터
				+ SHorizontalBox::Slot().Padding(5.f)
				[
					SNew(SScrollBox)
					+ SScrollBox::Slot()
					.VAlign(VAlign_Top)
					[
						SNew(SListView<TSharedPtr<FActionTriggerData>>)
						.ItemHeight(24)
						.ListItemsSource(&tool.Pin()->GetSelectedActionTriggerData())
						.OnGenerateRow        (this, &Widget_ActionData::OnGenerateRowForActionTriggerDataList )
						.OnSelectionChanged   (this, &Widget_ActionData::OnSelectionChangedForActionTriggerDataList)
					]
				]
				// 트리거 리스트
				+ SHorizontalBox::Slot().AutoWidth()
				[
					SNew(SBox)
					.WidthOverride(250)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().Padding(5.f).AutoHeight()
						[
							GetWidget_ActionBasicData()
						]
						+SVerticalBox::Slot().Padding(5.f).AutoHeight()
						[
							SNew(SButton)
							.Text(FText::FromString(TEXT("Trigger")))
							.OnClicked_Lambda([this]()
							{
								tool.Pin()->GetSelectedActionTriggerData().Add(MakeShareable(UActionData::CreateActionTriggerForEditor()));
								tool.Pin()->GetSelectedActionData()->MakeDirty();
								return FReply::Handled();
							})
						]
					]
				]
			]
		]
		// 선택이 안됐을 때
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SVerticalBox)
			.Visibility_Lambda([this](){return tool.Pin()->GetSelectedActionData() ? EVisibility::Collapsed : EVisibility::Visible;})
			+SVerticalBox::Slot()
			.Padding(5.f)
			.FillHeight(1.f)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FColor(192, 192, 192, 255))
				[
					SNew(STextBlock)
					.Text(FText::FromString("ActionInfo is Not Selected"))
				]
			]
		]
	];
}

TSharedRef<SWidget> Widget_ActionData::GetWidget_ActionBasicData()
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot()
	.Padding(5.f)
	.MaxHeight(24.f)
	.AutoHeight()
	[
		SNew(STextBlock)
		.Text_Lambda([this]()
		{
			return FText::FromString(tool.Pin()->GetSelectedActionData() ? tool.Pin()->GetSelectedActionData()->GetName() : TEXT(""));
		})
	]
	+SVerticalBox::Slot()
	.Padding(5.f)
	.MaxHeight(24.f)
	.AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Type")))
		]
		+SHorizontalBox::Slot()
		[
			SNew(SEnumComboBox, StaticEnum<EActionTypes>())
			.CurrentValue_Lambda([this]()
			{
				return tool.Pin()->GetSelectedActionData() ? static_cast<int32>(tool.Pin()->GetSelectedActionData()->actionType) : 0;
			})
			.OnEnumSelectionChanged_Lambda([this](int32 enumValue, ESelectInfo::Type selectInfoType)
			{
				const auto pActionData = tool.Pin()->GetSelectedActionData();
				if (pActionData)
				{
					const auto newActionType = static_cast<EActionTypes>(enumValue);
					if (pActionData->actionType != newActionType)
					{
						pActionData->actionType = newActionType;
						pActionData->MakeDirty();
					}
				}
			})
		]
	]
	+SVerticalBox::Slot()
	.Padding(5.f)
	.MaxHeight(24.f)
	.AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Length(sec)")))
		]
		+SHorizontalBox::Slot()
		[
			SNew(SNumericEntryBox<float>)
			.Value_Lambda([this]()
			{
				return tool.Pin()->GetSelectedActionData() ? tool.Pin()->GetSelectedActionData()->fLength : 0.f;
			})
			.OnValueChanged_Lambda([this](float floatValue)
			{
				const auto pActionData = tool.Pin()->GetSelectedActionData();
				if (pActionData && pActionData->fLength != floatValue)
				{
					pActionData->fLength = floatValue;
					pActionData->MakeDirty();
				}
			})
			.MinValue(0.f)
			.MaxValue(-1.f)
		]
	]
	+SVerticalBox::Slot()
	.Padding(5.f)
	.MaxHeight(24.f)
	.AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("IsLoop")))
		]
		+SHorizontalBox::Slot()
		[
			SNew(SCheckBox)
			.IsChecked_Lambda([this]()
			{
				if (!tool.Pin()->GetSelectedActionData())
					return  ECheckBoxState::Undetermined;

				return tool.Pin()->GetSelectedActionData()->bIsLoop ?  ECheckBoxState::Checked : ECheckBoxState::Unchecked;
			})
			.OnCheckStateChanged_Lambda([this](ECheckBoxState state)
			{
				const auto pActionData = tool.Pin()->GetSelectedActionData();
				if (!pActionData)
					return;

				bool newIsLoop = false;

				switch (state)
				{
					case ECheckBoxState::Checked : newIsLoop = true;	break;
					default:											break;
				}

				if (pActionData->bIsLoop != newIsLoop)
				{
					pActionData->bIsLoop = newIsLoop;
					pActionData->MakeDirty();
				}
			})
		]
	];
}

TSharedRef<ITableRow> Widget_ActionData::OnGenerateRowForActionEventDataList(TSharedPtr<FActionEventDataBase> InInfo,const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<FActionEventDataBase>>, OwnerTable)
	.Padding(2.f)
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot().AutoHeight()
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(255, 0, 198, 255))
			.Visibility_Lambda([this, InInfo]()
			{
				int idx = -1;
				tool.Pin()->GetSelectedActionEventData().Find(InInfo, idx);

				if (idx > 0 && tool.Pin()->GetSelectedActionEventData()[idx - 1]->GetActionEventType() == InInfo->GetActionEventType())
					return EVisibility::Collapsed;

				return EVisibility::Visible;
			})
			.ContentScale(1.5f)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString(InInfo->GetActionEventName()))
			]
		]
		+SVerticalBox::Slot().AutoHeight()
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(198, 198, 198, 255))
			.Content()
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot().AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot().AutoWidth()
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().AutoHeight().Padding(2.5f)
						[
							SNew(SButton)
							.VAlign(EVerticalAlignment::VAlign_Center)
							.HAlign(EHorizontalAlignment::HAlign_Center)
							.Text_Lambda([InInfo]()
							{
								if (InInfo->GetFolded_EditorContentsWidget())
									return FText::FromString(TEXT("▼"));
								else
									return FText::FromString(TEXT("▲"));
							})
							.OnClicked_Lambda([this, InInfo]()
							{
								InInfo->SetFolded_EditorContentsWidget(!InInfo->GetFolded_EditorContentsWidget());
								return FReply::Handled();
							})
						]
					]
					+SHorizontalBox::Slot()
					[
						InInfo->GetEditorTimeWidget(tool.Pin()->GetSelectedActionData())
					]
					+SHorizontalBox::Slot().AutoWidth()
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().AutoHeight().Padding(2.5f)
						[
							SNew(SButton)
							.Visibility_Lambda([this, InInfo]()
							{
								auto pEventType = InInfo.Get()->GetActionEventType();
								if (pEventType != EActionEventTypes::Animation)
									return EVisibility::Visible;

								int nAnimEventCount = 0;
								for (auto pActionEvent : tool.Pin()->GetSelectedActionEventData())
								{
									if (pActionEvent->GetActionEventType() == EActionEventTypes::Animation)
										continue;
									
									if (++nAnimEventCount > 1)
										return EVisibility::Visible;
								}

								return EVisibility::Hidden;
							})
							.VAlign(EVerticalAlignment::VAlign_Center)
							.HAlign(EHorizontalAlignment::HAlign_Center)
							.Text(FText::FromString(TEXT("X")))
							.ForegroundColor(FColor::White)
							.ButtonColorAndOpacity(FColor::Red)
							.OnClicked_Lambda([this, InInfo]()
							{
								tool.Pin()->GetSelectedActionEventData().Remove(InInfo);
								tool.Pin()->GetSelectedActionData()->MakeDirty();
								return FReply::Handled();
							})
						]
					]
				]
				+SVerticalBox::Slot().AutoHeight()
				[
					SNew(SBox)
					.Visibility_Lambda([InInfo](){return InInfo->GetFolded_EditorContentsWidget() ? EVisibility::Collapsed : EVisibility::Visible;})
					.Content()
					[
						InInfo->GetEditorContentsWidget(tool.Pin()->GetSelectedActionData())
					]
				]
			]
		]
	];
}

void Widget_ActionData::OnSelectionChangedForActionEventDataList(TSharedPtr<FActionEventDataBase> selectedValue, ESelectInfo::Type type)
{
	
}

TSharedRef<ITableRow> Widget_ActionData::OnGenerateRowForActionTriggerDataList(TSharedPtr<FActionTriggerData> InInfo,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<FActionEventDataBase>>, OwnerTable)
	.Padding(2.f)
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot().AutoHeight()
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(198, 198, 198, 255))
			.Content()
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot().AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot().AutoWidth()
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().AutoHeight().Padding(2.5f)
						[
							SNew(SButton)
							.VAlign(EVerticalAlignment::VAlign_Center)
							.HAlign(EHorizontalAlignment::HAlign_Center)
							.Text_Lambda([InInfo]()
							{
								if (InInfo->GetFolded_EditorContentsWidget())
									return FText::FromString(TEXT("▼"));
								else
									return FText::FromString(TEXT("▲"));
							})
							.OnClicked_Lambda([this, InInfo]()
							{
								InInfo->SetFolded_EditorContentsWidget(!InInfo->GetFolded_EditorContentsWidget());
								return FReply::Handled();
							})
						]
					]
					+SHorizontalBox::Slot()
					[
						InInfo->GetEditorTimeWidget(tool.Pin()->GetSelectedActionData())
					]
					+SHorizontalBox::Slot().AutoWidth()
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().AutoHeight().Padding(2.5f)
						[
							SNew(SButton)
							.Visibility_Lambda([this]()
							{
								return tool.Pin()->GetSelectedActionTriggerData().Num() > 1 ? EVisibility::Visible : EVisibility::Hidden;
							})
							.VAlign(EVerticalAlignment::VAlign_Center)
							.HAlign(EHorizontalAlignment::HAlign_Center)
							.Text(FText::FromString(TEXT("X")))
							.ForegroundColor(FColor::White)
							.ButtonColorAndOpacity(FColor::Red)
							.OnClicked_Lambda([this, InInfo]()
							{
								tool.Pin()->GetSelectedActionTriggerData().Remove(InInfo);
								tool.Pin()->GetSelectedActionData()->MakeDirty();
								return FReply::Handled();
							})
						]
					]
				]
				+SVerticalBox::Slot().AutoHeight()
				[
					SNew(SBox)
					.Visibility_Lambda([InInfo](){return InInfo->GetFolded_EditorContentsWidget() ? EVisibility::Collapsed : EVisibility::Visible;})
					.Content()
					[
						InInfo->GetEditorContentsWidget(tool.Pin()->GetSelectedActionData())
					]
				]
			]
		]
	];

}

void Widget_ActionData::OnSelectionChangedForActionTriggerDataList(TSharedPtr<FActionTriggerData> selectedValue,
	ESelectInfo::Type type)
{
}
