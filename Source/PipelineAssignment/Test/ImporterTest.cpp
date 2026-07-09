#include "ImporterTest.h"

#include "../Importer/SceneImporter.h"
#include "../Importer/MaterialImporter.h"

#include "../Builder/SceneBuilder.h"
#include "../Builder/MaterialAssigner.h"

#include "../Importer/AssetMatcher.h"
#include "../Renamer/MaterialRenamer.h"

#include "../Builder/HierarchyBuilder.h"

#include "TimerManager.h"


#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"

void AImporterTest::BeginPlay()
{
    Super::BeginPlay();

    FSceneImporter Importer;
    FMaterialImporter MaterialImporter;
    FSceneBuilder Builder;
    FMaterialAssigner Assigner;

    FMaterialRenamer Renamer;
    FAssetMatcher Matcher;
    //FHierarchyBuilder HierarchyBuilder;
    
    
    Renamer.RenameMaterials();
    Matcher.Initialize();

    TArray<FMeshData> Meshes;
    TArray<FMaterialData> Materials;

    FString SceneFilePath = TEXT("D:/Game Engine/Maya Projects/MayaUnreal/PipelineAssignment/Json/scene.json");

    FString MaterialFilePath = TEXT("D:/Game Engine/Maya Projects/MayaUnreal/PipelineAssignment/Json/material_data.json");

    TArray<AStaticMeshActor*> Actors;

    if (Importer.LoadScene(SceneFilePath, Meshes))
    {
        Actors = Builder.BuildScene(GetWorld(), Meshes);
        // HierarchyBuilder.BuildHierarchy(Meshes, Actors);
    }

    if (MaterialImporter.LoadMaterials(MaterialFilePath, Materials))
    {
        UE_LOG(LogTemp, Warning, TEXT("Loaded %d Materials"), Materials.Num());
    }

    Assigner.AssignMaterials(Actors, Materials);
    GetWorld()->GetTimerManager().SetTimerForNextTick(
    [this, Meshes, Actors]()
    {
        FHierarchyBuilder Builder;
        Builder.BuildHierarchy(Meshes, Actors);
    });
}