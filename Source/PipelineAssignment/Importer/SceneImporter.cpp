#include "SceneImporter.h"

#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool FSceneImporter::LoadScene(const FString& FilePath, TArray<FMeshData>& Meshes)
{
    FString JsonString;

    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        return false;
    }
    
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    if (!FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        return false;
    }

    const TArray<TSharedPtr<FJsonValue>>* MeshArray;

    if (!JsonObject->TryGetArrayField(TEXT("Meshes"), MeshArray))
    {
        return false;
    }

    for (const TSharedPtr<FJsonValue>& Value : *MeshArray)
    {
        TSharedPtr<FJsonObject> MeshObject = Value->AsObject();

        if (!MeshObject.IsValid())
        {
            continue;
        }

        FMeshData Mesh;

        MeshObject->TryGetStringField(TEXT("Original_Name"), Mesh.OriginalName);
        MeshObject->TryGetStringField(TEXT("Clean_Name"), Mesh.CleanName);
        MeshObject->TryGetStringField(TEXT("Parent"), Mesh.Parent );

        MeshObject->TryGetNumberField(TEXT("Vertices"), Mesh.Vertices);
        MeshObject->TryGetNumberField(TEXT("Triangles"), Mesh.Triangles);

        MeshObject->TryGetStringField(TEXT("Material"), Mesh.Material);

        const TArray<TSharedPtr<FJsonValue>>* PositionArray;

        if (MeshObject->TryGetArrayField(TEXT("Position"), PositionArray))
        {
            Mesh.Position = FVector(
                (*PositionArray)[0]->AsNumber(),
                (*PositionArray)[1]->AsNumber(),
                (*PositionArray)[2]->AsNumber()
            );
        }

        const TArray<TSharedPtr<FJsonValue>>* RotationArray;

        if (MeshObject->TryGetArrayField(TEXT("Rotation"), RotationArray))
        {
            Mesh.Rotation = FRotator(
                (*RotationArray)[0]->AsNumber(),
                (*RotationArray)[1]->AsNumber(),
                (*RotationArray)[2]->AsNumber()
            );
        }

        const TArray<TSharedPtr<FJsonValue>>* ScaleArray;

        if (MeshObject->TryGetArrayField(TEXT("Scale"), ScaleArray))
        {
            Mesh.Scale = FVector(
                (*ScaleArray)[0]->AsNumber(),
                (*ScaleArray)[1]->AsNumber(),
                (*ScaleArray)[2]->AsNumber()
            );
        }
        Meshes.Add(Mesh);
    }

    return true;
}