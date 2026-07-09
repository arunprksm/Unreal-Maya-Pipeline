#include "MaterialRenamer.h"

#include "../Importer/MaterialImporter.h"
#include "../Data/MaterialData.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "ObjectTools.h"

void FMaterialRenamer::RenameMaterials()
{
    FMaterialImporter Importer;

    TArray<FMaterialData> Materials;

    FString FilePath = TEXT("D:/Game Engine/Maya Projects/MayaUnreal/PipelineAssignment/Json/material_data.json");

    if (!Importer.LoadMaterials(FilePath, Materials))
    {
        return;
    }

    FAssetRegistryModule& AssetRegistry =
        FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    TArray<FAssetData> Assets;

    AssetRegistry.Get().GetAssetsByPath(
        FName("/Game/Imported"),
        Assets,
        false);

    for (const FMaterialData& Material : Materials)
    {
        for (const FAssetData& Asset : Assets)
        {
            if (Asset.AssetClassPath.GetAssetName() != TEXT("Material"))
            {
                continue;
            }

            FString Existing = Asset.AssetName.ToString();

            FString CleanExisting = Existing;
            CleanExisting.ReplaceInline(TEXT("_"), TEXT(""));

            FString CleanTarget = Material.MaterialName;
            CleanTarget.ReplaceInline(TEXT("_"), TEXT(""));

            if (!(CleanExisting.Contains(TEXT("TopSeatMaterial")) &&
                CleanTarget.Contains(TEXT("TopSeatMaterial"))))
            {
                if (!CleanExisting.Contains(CleanTarget))
                {
                    continue;
                }
            }

            UObject* Object = Asset.GetAsset();

            if (!Object)
            {
                continue;
            }

            FAssetToolsModule& AssetTools =
                FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");

            AssetTools.Get().RenameAssets({
                FAssetRenameData(
                    Object,
                    TEXT("/Game/Imported"),
                    Material.MaterialName)
            });

            UE_LOG(LogTemp, Warning, TEXT("Renamed %s -> %s"),
                *Existing,
                *Material.MaterialName);

            break;
        }
    }
}