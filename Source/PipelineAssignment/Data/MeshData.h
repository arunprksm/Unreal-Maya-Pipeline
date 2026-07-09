#pragma once

#include "CoreMinimal.h"
#include "MeshData.generated.h"

USTRUCT(BlueprintType)
struct FMeshData
{
    GENERATED_BODY()
public:
        
    UPROPERTY()
    FString OriginalName;

    UPROPERTY()
    FString CleanName;

    UPROPERTY()
    FString Parent;

    UPROPERTY()
    FVector Position;

    UPROPERTY()
    FRotator Rotation;

    UPROPERTY()
    FVector Scale;

    UPROPERTY()
    int32 Vertices;

    UPROPERTY()
    int32 Triangles;

    UPROPERTY()
    FString Material;
};