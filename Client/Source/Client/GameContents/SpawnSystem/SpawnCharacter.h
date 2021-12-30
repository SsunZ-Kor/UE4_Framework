#pragma once

#include "Client/Framework/GameCharacter/GameCharacter.h"
#include "SpawnCharacter.generated.h"

UCLASS()
class CLIENT_API ASpawnCharacter : public AGameCharacter
{
	GENERATED_BODY()

protected:
	TDoubleLinkedListEx<ASpawnCharacter*>::TDoubleLinkedListExNode* m_pNode_Spawn; 

protected:	
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	TDoubleLinkedListEx<ASpawnCharacter*>::TDoubleLinkedListExNode* const& GetSpawnNode();
};