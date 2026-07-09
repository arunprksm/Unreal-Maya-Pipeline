#pragma once

#include "CoreMinimal.h"
#include "../Data/MaterialData.h"

class FMaterialImporter
{
public:

	bool LoadMaterials(const FString& FilePath, TArray<FMaterialData>& Materials);
};