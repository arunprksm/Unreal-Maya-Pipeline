#include "SceneBuilder.h"

#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

#include "../Importer/AssetMatcher.h"

TArray<AStaticMeshActor*> FSceneBuilder::BuildScene(UWorld* World, const TArray<FMeshData>& Meshes)
{
    TArray<AStaticMeshActor*> SpawnedActors;

    FAssetMatcher Matcher;
    Matcher.Initialize();

    for (const FMeshData& Mesh : Meshes)
    {
        UStaticMesh* StaticMesh = Matcher.FindBestMesh(Mesh.CleanName);

        if (!StaticMesh)
        {
            UE_LOG(LogTemp, Warning, TEXT("Couldn't find mesh: %s"), *Mesh.CleanName);
            continue;
        }

        AStaticMeshActor* Actor = World->SpawnActor<AStaticMeshActor>(Mesh.Position, Mesh.Rotation);

        Actor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
        Actor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
        Actor->SetActorScale3D(Mesh.Scale);
        Actor->SetActorLabel(Mesh.CleanName);

        UE_LOG(LogTemp, Warning, TEXT("Spawned %s"), *Actor->GetActorLabel());

        UE_LOG(LogTemp, Warning, TEXT("Actor Root = %s"), 
            Actor->GetRootComponent()
                ? *Actor->GetRootComponent()->GetName()
                : TEXT("NULL"));
        SpawnedActors.Add(Actor);
    }

    return SpawnedActors;
}