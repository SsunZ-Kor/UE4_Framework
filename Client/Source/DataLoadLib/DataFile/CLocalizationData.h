// Generate By DataTool. 2021-12-04 오전 5:52:02
// Generated only one time when file is not exists.
// Drum
#pragma once

enum class ELanguage : uint8;

class DATALOADLIB_API CLocalizationData
{
public:
	FString ID;
	FString Korean;
	FString English;
	FString Japanese;

static FString KEY_EMPTY;

	void SetInfo(const struct FRowDataInfo& fInfo);

	const FString& GetLanguage(int nIndex) const;

	const FString& GetLanguage(ELanguage eLanguage) const;
};
