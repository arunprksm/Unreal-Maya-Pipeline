#pragma once

#include "CoreMinimal.h"
#include "../Data/MeshData.h"

class AStaticMeshActor;

class FHierarchyBuilder
{
public:
    void BuildHierarchy(const TArray<FMeshData>& Meshes, const TArray<AStaticMeshActor*>& Actors);
};