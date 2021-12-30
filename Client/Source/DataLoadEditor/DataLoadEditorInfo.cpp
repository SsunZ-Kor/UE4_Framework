#include "DataLoadEditorInfo.h"

DEFINE_LOG_CATEGORY(DLE);

const FString DataLoadEditorInfo::BYTE_EXTS = TEXT("bytes");
const FString DataLoadEditorInfo::UASSET_EXTS = TEXT("uasset");
const FString DataLoadEditorInfo::PATH_RELATIVE_BINARY_ROOT = FPaths::ProjectContentDir() / TEXT("GameContents");