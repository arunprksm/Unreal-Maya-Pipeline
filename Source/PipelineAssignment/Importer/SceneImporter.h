#pragma once

#include "CoreMinimal.h"
#include "../Data/MeshData.h"

class FSceneImporter
{
public:
    bool LoadScene(const FString& FilePath, TArray<FMeshData>& Meshes);
};