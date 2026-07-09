#pragma once

#include "CoreMinimal.h"

class UMaterialInterface;

class FMaterialMatcher
{
public:

    void Initialize();

    UMaterialInterface* FindBestMaterial(const FString& CleanMaterialName);

private:

    TArray<UMaterialInterface*> Materials;
};