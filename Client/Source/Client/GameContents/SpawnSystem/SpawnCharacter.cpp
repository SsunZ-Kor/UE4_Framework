#include "SpawnCharacter.h"
#include "SpawnPoint.h"

void ASpawnCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_pNode_Spawn = nullptr;
}

void ASpawnCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	if (m_pNode_Spawn)
	{
		m_pNode_Spawn->RemoveSelf();
		delete m_pNode_Spawn;
		m_pNode_Spawn = nullptr;
	}
}

TDoubleLinkedListEx<ASpawnCharacter*>::TDoubleLinkedListExNode* const& ASpawnCharacter::GetSpawnNode()
{
	if (!m_pNode_Spawn)
		m_pNode_Spawn = new TDoubleLinkedListEx<ASpawnCharacter*>::TDoubleLinkedListExNode(this);
	
	return m_pNode_Spawn;
}