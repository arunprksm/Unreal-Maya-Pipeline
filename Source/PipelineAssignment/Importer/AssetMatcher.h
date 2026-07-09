#pragma once

#include "CoreMinimal.h"

class UStaticMesh;

class FAssetMatcher
{
public:

    bool Initialize();

    UStaticMesh* FindBestMesh(const FString& CleanName);

private:

    FString NormalizeName(const FString& Name) const;

private:

    TArray<UStaticMesh*> StaticMeshes;
};