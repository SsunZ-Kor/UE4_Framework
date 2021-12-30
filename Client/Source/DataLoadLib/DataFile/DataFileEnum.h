// Generate By DataTool. 2021-12-04 오전 5:52:02
// Drum
#pragma once

UENUM()
enum class EDataFileEnum : uint8
{
	ConstData = 0,
	CharacterData = 1,
	HelpData = 2,
	StatData = 3,
	ItemData = 4,
	HelpCategoryData = 5,
	MAX,
};

UENUM()
enum class ELanguage : uint8
{
	None = 0,
	Korean = 1,
	English = 2,
	Japanese = 3,
};
