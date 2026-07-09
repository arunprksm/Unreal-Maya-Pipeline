#pragma once

#include "CoreMinimal.h"
#include "../Data/MaterialData.h"

class UMaterialInterface;
class AStaticMeshActor;

class FMaterialAssigner
{
public:

    void AssignMaterials(const TArray<AStaticMeshActor*>& Actors, const TArray<FMaterialData>& Materials);
};