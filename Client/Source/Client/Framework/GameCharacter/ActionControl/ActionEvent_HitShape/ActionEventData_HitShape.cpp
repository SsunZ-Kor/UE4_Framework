// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_HitShape.h"
#include "ActionEventRuntime_HitShape.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FHitShapeInfo::FHitShapeInfo()
{
	m_CastType = ECastTypes::MyPos_Box;
	m_fDist = 0.f;

	m_vOffsetPos = FVector(100.f, 0.f, 0.f);
	m_qOffsetRot = FQuat::Identity;
	m_Size = FVector(200.f, 200.f, 200.f);
}

FHitShapeInfo::~FHitShapeInfo()
{
}

FActionEventData_HitShape::FActionEventData_HitShape()
{
	m_TargetType = EGameCharacterFindTargetTypes::Enemy;
	m_bIsFollow = false;
	m_hitInfos.Add(FHitShapeInfo());
}

FActionEventData_HitShape::~FActionEventData_HitShape()
{
}

CreateRuntimeResult FActionEventData_HitShape::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_HitShape>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_HitShape::GetActionEventType() const
{
	return EActionEventTypes::HitShape;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_HitShape::GetEditorContentsWidget(UActionData* pActionData)
{
	m_hitInfos_Editor.Empty();
	for (auto& hitInfo : m_hitInfos)
		m_hitInfos_Editor.Add(MakeShareable(new FHitShapeInfo(hitInfo)));
	
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			EditorEnum<EGameCharacterFindTargetTypes>(TEXT("TargetTypes"), m_TargetType, pActionData)
		]
		+SHorizontalBox::Slot()
		[
			EditorBool(TEXT("Follow FX/SFX"), m_bIsFollow, pActionData)
		]
		+SHorizontalBox::Slot()
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorString(TEXT("RefPath FX"), m_ResPath_FX, pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorString(TEXT("RefPath SFX"), m_ResPath_SFX, pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorList<TSharedPtr<FHitShapeInfo>>(
			TEXT("HitShapeInfo"),
			m_hitInfos_Editor,
			m_bIsFolded_HitInfos,
			SListView<TSharedPtr<FHitShapeInfo>>::FOnGenerateRow::CreateLambda(
				[this, pActionData](TSharedPtr<FHitShapeInfo> InInfo,const TSharedRef<STableViewBase>& OwnerTable)
				{
					return SNew(STableRow<TSharedPtr<FHitShapeInfo>>, OwnerTable)
						.Padding(2.f)
					[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								SNew(SVerticalBox)
								+SVerticalBox::Slot()
								[
									SNew(SHorizontalBox)
									+SHorizontalBox::Slot()
									[
										EditorEnum(TEXT("CastType"), InInfo->m_CastType, pActionData)
									]
									+SHorizontalBox::Slot()
									[
										EditorFloat(TEXT("Dist"), InInfo->m_fDist, pActionData)
									]
								]
								+SVerticalBox::Slot()
								[
									EditorVector(TEXT("Offset Loc"), InInfo->m_vOffsetPos, pActionData)
								]
								+SVerticalBox::Slot()
								[
									EditorQuat(TEXT("Offset Rot"), InInfo->m_qOffsetRot, pActionData)
								]
								+SVerticalBox::Slot()
								[
									EditorVector(TEXT("Size"), InInfo->m_Size, pActionData)
								]
							]
							+SHorizontalBox::Slot().AutoWidth()
							[
								SNew(SVerticalBox)
								+SVerticalBox::Slot().AutoHeight().Padding(2.5f)
								[
									SNew(SButton)
									.VAlign(EVerticalAlignment::VAlign_Center)
									.HAlign(EHorizontalAlignment::HAlign_Center)
									.Text(FText::FromString(TEXT("X")))
									.ForegroundColor(FColor::White)
									.ButtonColorAndOpacity(FColor::Red)
									.Visibility_Lambda([this]()
									{
										return m_hitInfos_Editor.Num() > 1 ? EVisibility::Visible : EVisibility::Hidden;
									})
									.OnClicked_Lambda([this, InInfo, pActionData]()
									{
										m_hitInfos_Editor.Remove(InInfo);
										pActionData->MakeDirty();
										return FReply::Handled();
									})
								]
							]
						];
				}),
			nullptr,
			FOnClicked::CreateLambda([this]()
			{
				m_hitInfos_Editor.Add(MakeShareable(new FHitShapeInfo));
				return FReply::Handled();
			}),
			pActionData)
	];
}

void FActionEventData_HitShape::AdjustEditorData()
{
	FActionEventDataBase::AdjustEditorData();

	m_hitInfos.Empty();
	for (auto pHitInfo : m_hitInfos_Editor)
		m_hitInfos.Add(FHitShapeInfo(*pHitInfo.Get()));
}
#endif
