#include "AssetMatcher.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/StaticMesh.h"

bool FAssetMatcher::Initialize()
{
    StaticMeshes.Empty();

    FAssetRegistryModule& AssetRegistry =
        FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    FARFilter Filter;

    Filter.ClassPaths.Add(UStaticMesh::StaticClass()->GetClassPathName());

    TArray<FAssetData> Assets;

    AssetRegistry.Get().GetAssets(Filter, Assets);

    for (const FAssetData& Asset : Assets)
    {
        UStaticMesh* Mesh = Cast<UStaticMesh>(Asset.GetAsset());

        if (Mesh)
        {
            StaticMeshes.Add(Mesh);

            UE_LOG(LogTemp, Warning,
                TEXT("Found Mesh : %s"),
                *Mesh->GetName());
        }
    }

    UE_LOG(LogTemp, Warning,
        TEXT("Total Static Meshes : %d"),
        StaticMeshes.Num());

    return StaticMeshes.Num() > 0;
}

FString FAssetMatcher::NormalizeName(const FString& Name) const
{
    FString Result = Name.ToLower();

    // Remove separators first
    Result.ReplaceInline(TEXT("_"), TEXT(""));
    Result.ReplaceInline(TEXT(" "), TEXT(""));

    // Remove digits
    for (int32 i = 0; i <= 9; i++)
    {
        Result.ReplaceInline(*FString::FromInt(i), TEXT(""));
    }

    // Remove known prefixes/suffixes
    Result.ReplaceInline(TEXT("samplemodel"), TEXT(""));
    Result.ReplaceInline(TEXT("final"), TEXT(""));

    return Result;
}

UStaticMesh* FAssetMatcher::FindBestMesh(const FString& CleanName)
{
    FString TargetName = NormalizeName(CleanName);

    for (UStaticMesh* Mesh : StaticMeshes)
    {
        if (!IsValid(Mesh))
        {
            continue;
        }

        FString MeshName = NormalizeName(Mesh->GetName());

        if (MeshName == TargetName)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("Matched %s -> %s"),
                *CleanName,
                *Mesh->GetName());

            return Mesh;
        }
    }

    UE_LOG(LogTemp, Warning,
        TEXT("No match found for %s"),
        *CleanName);

    return nullptr;
}