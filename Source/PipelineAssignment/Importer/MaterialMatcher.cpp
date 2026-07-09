#include "MaterialMatcher.h"

#include "Materials/MaterialInterface.h"
#include "AssetRegistry/AssetRegistryModule.h"

void FMaterialMatcher::Initialize()
{
    Materials.Empty();

    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    TArray<FAssetData> AssetList;

    AssetRegistryModule.Get().GetAssetsByPath(FName("/Game/Imported"), AssetList, true);

    UE_LOG(LogTemp, Warning, TEXT("Assets Found : %d"), AssetList.Num());

    for (const FAssetData& Asset : AssetList)
    {
        UObject* Object = Asset.GetAsset();

        if (!Object)
        {
            continue;
        }

        UMaterialInterface* Material = Cast<UMaterialInterface>(Object);

        if (Material)
        {
            Materials.Add(Material);

            UE_LOG(LogTemp, Warning, TEXT("Found Material : %s"), *Material->GetName());
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Total Materials : %d"), Materials.Num());
}

UMaterialInterface* FMaterialMatcher::FindBestMaterial(const FString& CleanMaterialName)
{
    FString SearchName = CleanMaterialName;

    SearchName.ReplaceInline(TEXT("_"), TEXT(""));
    SearchName.ReplaceInline(TEXT(" "), TEXT(""));
    SearchName = SearchName.ToLower();

    for (UMaterialInterface* Material : Materials)
    {
        FString MaterialName = Material->GetName();

        MaterialName.ReplaceInline(TEXT("_"), TEXT(""));
        MaterialName.ReplaceInline(TEXT(" "), TEXT(""));
        MaterialName = MaterialName.ToLower();

        FString TempMaterial = MaterialName;
        FString TempSearch = SearchName;

        TempMaterial.RemoveSpacesInline();
        TempSearch.RemoveSpacesInline();

        TempMaterial.ReplaceInline(TEXT("9836589"), TEXT(""));

        if (TempMaterial.Contains(TempSearch))
        {
            UE_LOG(LogTemp, Warning,
                TEXT("Matched Material %s -> %s"),
                *CleanMaterialName,
                *Material->GetName());

            return Material;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Couldn't match material: %s"), *CleanMaterialName);

    return nullptr;
}