// Generate By DataTool. 2021-10-22 오후 9:02:37
// Generated only one time when file is not exists.
// Drum
#pragma once

class CLocalizationData
{
public:
	FString ID;
	FString KO;
	FString EN;
	FString JA;

	void SetInfo(const struct FRowDataInfo& fInfo);

	const FString GetLanguage(int nIndex) const;

	const FString GetLanguage(enum class ELanguage eLanguage) const;
};
