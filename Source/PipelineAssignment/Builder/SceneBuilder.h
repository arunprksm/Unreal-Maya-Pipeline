#pragma once

#include "CoreMinimal.h"
#include "../Data/MeshData.h"

class AStaticMeshActor;

class FSceneBuilder
{
public:

    TArray<AStaticMeshActor*> BuildScene(UWorld* World, const TArray<FMeshData>& Meshes);
};