#include "Widget_ActionList.h"

#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"

void Widget_ActionList::Construct(const FArguments& InArgs)
{
    tool = InArgs._Tool;
    if (!tool.IsValid())
        return;

    tool.Pin()->RefreshAllActionDataInfo();
    auto& actionDataInfos = tool.Pin()->GetFilteredActionDataInfos();

    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot().Padding(5.f).MaxHeight(24.f).AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            [
                SNew(SEditableTextBox)
                .Text(tool.Pin()->GetFilterText())
                .OnTextChanged(FOnTextChanged::CreateLambda([this](const FText& txt)
                {
                    tool.Pin()->SetFilterText(txt);
                }))
            ]
            + SHorizontalBox::Slot().AutoWidth()
            [
                SNew(SButton)
                .Text(FText::FromString(TEXT("Search")))
                .OnClicked(FOnClicked::CreateLambda([this]()
                {
                    tool.Pin()->RefreshFilteredActionDataInfos();
                    return FReply::Handled();
                }))
            ]
        ]
        + SVerticalBox::Slot().Padding(5.f).MaxHeight(24.f).AutoHeight()
        [
            SNew(SButton).
            VAlign(VAlign_Center).HAlign(HAlign_Center)
            .Text(FText::FromString(TEXT("Save")))
            .OnClicked_Lambda([this]()
            {
                tool.Pin()->SaveSelectedActionData();
                return FReply::Handled();
            })
        ]
        + SVerticalBox::Slot().Padding(5.f)
        [
            SNew(SScrollBox)
            + SScrollBox::Slot()
            .VAlign(VAlign_Top)
            [
              SAssignNew(m_ListView, SListView<TSharedPtr<ActionDataInfo>>)
              .ItemHeight(24)
              .ListItemsSource(&actionDataInfos)
              .OnGenerateRow        (this, &Widget_ActionList::OnGenerateRowForActionDataList )
              .OnSelectionChanged   (this, &Widget_ActionList::OnSelectionChangedForActionDataList)
            ]
        ]
        //+ SVerticalBox::Slot().Padding(5.f).MaxHeight(24.f).AutoHeight()
        //[
        //    SNew(SButton)
        //    .VAlign(VAlign_Center).HAlign(HAlign_Center)
        //    .Text(FText::FromString(TEXT("Test")))
        //]
    ];
}

TSharedRef<ITableRow> Widget_ActionList::OnGenerateRowForActionDataList(TSharedPtr<ActionDataInfo> InInfo,const TSharedRef<STableViewBase>& OwnerTable)
{
    return SNew(STableRow<TSharedPtr<ActionDataInfo>>, OwnerTable)
        .Padding(2.f)
        [
            SNew(STextBlock).Text(FText::FromString(InInfo->Name))
        ];
}

void Widget_ActionList::OnSelectionChangedForActionDataList(TSharedPtr<ActionDataInfo> selectedValue, ESelectInfo::Type type)
{
    auto pSelectedActionData = tool.Pin()->GetSelectedActionData();
    if (pSelectedActionData && pSelectedActionData->IsDirty())
    {
        switch (FMessageDialog::Open(EAppMsgType::YesNoCancel, FText::FromString(TEXT("변경사항이 있습니다.\n\n저장하시겠습니까?")), nullptr))
        {
        case EAppReturnType::Yes:
            tool.Pin()->SaveSelectedActionData();
            break;
        case EAppReturnType::No:
            break;
        case EAppReturnType::Cancel:
            m_ListView->SetSelection(tool.Pin()->GetSelectedActionDataInfo());
            return;
        default:
            break;
        }
    }

    tool.Pin()->LoadSelectedActionData(selectedValue);
}
