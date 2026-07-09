#include "MaterialAssigner.h"

#include "../Importer/MaterialMatcher.h"
#include "../Importer/AssetMatcher.h"

#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

void FMaterialAssigner::AssignMaterials(const TArray<AStaticMeshActor*>& Actors, const TArray<FMaterialData>& Materials)
{
    FAssetMatcher AssetMatcher;
    AssetMatcher.Initialize();

    FMaterialMatcher MaterialMatcher;
    MaterialMatcher.Initialize();

    for (AStaticMeshActor* Actor : Actors)
    {
        if (!Actor)
        {
            continue;
        }

        UStaticMesh* ActorMesh = Actor->GetStaticMeshComponent()->GetStaticMesh();

        if (!ActorMesh)
        {
            continue;
        }

        for (const FMaterialData& Material : Materials)
        {
            bool bMatch = false;

            for (const FString& Target : Material.SceneTargets)
            {
                UStaticMesh* TargetMesh = AssetMatcher.FindBestMesh(Target);

                if (TargetMesh == ActorMesh)
                {
                    bMatch = true;
                    break;
                }
            }

            if (!bMatch)
            {
                continue;
            }

            UMaterialInterface* UnrealMaterial =
                MaterialMatcher.FindBestMaterial(Material.MaterialName);

            if (!UnrealMaterial)
            {
                UE_LOG(LogTemp, Warning, TEXT("Couldn't match material %s"), *Material.MaterialName);
                continue;
            }

            Actor->GetStaticMeshComponent()->SetMaterial(0, UnrealMaterial);

            UE_LOG(LogTemp, Warning,
                TEXT("Assigned %s -> %s"),
                *UnrealMaterial->GetName(),
                *ActorMesh->GetName());

            break;
        }
    }
}