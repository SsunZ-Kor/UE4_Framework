// #pragma once
//
// #include "../../Framework/ClientGameBase.h"
// #include "StatData.generated.h"
//
// USTRUCT(BlueprintType)
// struct FStatData : public FTableRowBase
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
// 	int				ATK;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	int				ATKRate;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	int				MaxHP;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
// 	int				MaxHPRate;
// };