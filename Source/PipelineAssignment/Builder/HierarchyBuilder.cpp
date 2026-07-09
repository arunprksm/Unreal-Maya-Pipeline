#include "HierarchyBuilder.h"
#include "Components/SceneComponent.h"

#include "HierarchyActor.h"

#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void FHierarchyBuilder::BuildHierarchy(
    const TArray<FMeshData>& Meshes,
    const TArray<AStaticMeshActor*>& Actors)
{
    if (Actors.Num() == 0)
    {
        return;
    }

    UWorld* World = Actors[0]->GetWorld();

    if (!World)
    {
        return;
    }

    // Existing mesh actors
    TMap<FString, AActor*> ActorMap;

    for (int32 i = 0; i < Meshes.Num(); i++)
    {
        if (Actors.IsValidIndex(i))
        {
            ActorMap.Add(Meshes[i].CleanName, Actors[i]);
        }
    }

    // Create missing parent actors
    for (const FMeshData& Mesh : Meshes)
    {
        if (Mesh.Parent.IsEmpty())
        {
            continue;
        }

        if (!ActorMap.Contains(Mesh.Parent))
        {
            FActorSpawnParameters Params;

            Params.Name = FName(*Mesh.Parent);

            // AHierarchyActor* ParentActor = World->SpawnActor<AHierarchyActor>(FTransform::Identity, Params);

            FTransform Transform = FTransform::Identity;
            AHierarchyActor* ParentActor = World->SpawnActor<AHierarchyActor>(AHierarchyActor::StaticClass(), Transform, Params);

            // AHierarchyActor* ParentActor = World->SpawnActor<AHierarchyActor>(AHierarchyActor::StaticClass(), FTransform::Identity, Params);
           
            ParentActor->SetActorLabel(Mesh.Parent);

            ActorMap.Add(Mesh.Parent, ParentActor);

            UE_LOG(LogTemp, Warning, TEXT("Created Parent : %s"), *Mesh.Parent);
        }
    }

    // Attach children
    for (int32 i = 0; i < Meshes.Num(); i++)
    {
        if (!Actors.IsValidIndex(i))
        {
            continue;
        }

        if (Meshes[i].Parent.IsEmpty())
        {
            continue;
        }

        UE_LOG(LogTemp, Warning, TEXT("Child = %s  Parent = %s"), *Meshes[i].CleanName, *Meshes[i].Parent);
        AActor** ParentActor = ActorMap.Find(Meshes[i].Parent);

        if (ParentActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("Found Parent Actor = %s"), *(*ParentActor)->GetActorLabel());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Parent NOT FOUND"));
        }

        bool bAttached = Actors[i]->AttachToActor(*ParentActor, FAttachmentTransformRules::KeepWorldTransform);

        UE_LOG(LogTemp, Warning, TEXT("Attach Result = %s"), bAttached ? TEXT("TRUE") : TEXT("FALSE"));
        AActor* Parent = Actors[i]->GetAttachParentActor();
        UE_LOG(LogTemp, Warning, TEXT("%s Parent Actor = %s"), *Actors[i]->GetActorLabel(), Parent ? *Parent->GetActorLabel() : TEXT("NULL"));

        Actors[i]->SetActorLabel(Meshes[i].CleanName);

        UE_LOG(LogTemp, Warning, TEXT("Attached %s -> %s"), *Meshes[i].CleanName, *Meshes[i].Parent);
    }
}