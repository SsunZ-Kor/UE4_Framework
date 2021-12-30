// #pragma once
//
// #include "../../Framework/ClientGameBase.h"
// #include "GameCharacterData.generated.h"
//
// USTRUCT(BlueprintType)
// struct FGameCharacterData : public FTableRowBase
// {
// 	GENERATED_BODY()
//
// public :
// 	static const wchar_t* FILE_NAME;
// 	static const int TABLE_UNIQUE_KEY;
//
// public:
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	int				Id;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	FString			Name;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	FString			refPath;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	FString			fileName_Model;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	FString			fileName_AnimInst;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	FString			fileName_AIBT;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	int				DataId_Stat;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	float			Height;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	float			Radius;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	float			Sight;
// };