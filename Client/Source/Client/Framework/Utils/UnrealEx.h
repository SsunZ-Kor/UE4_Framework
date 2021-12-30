#pragma once

FBodyInstance* HitResultToBodyInst(const FHitResult* const pHitResult);
FBodyInstance* HitResultToBodyInst(const FHitResult& hitResult);
void GetAllFilesInDirectory(TArray<FString>& results, const FString directory, const bool fullPath, const FString onlyFilesStartingWith, const FString onlyFilesWithExtension);
