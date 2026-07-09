#include "MaterialImporter.h"

#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool FMaterialImporter::LoadMaterials(const FString& FilePath, TArray<FMaterialData>& Materials)
{
	FString JsonString;

	if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
	{
		return false;
	}

	TSharedPtr<FJsonObject> RootObject;

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, RootObject))
	{
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* JsonMaterials;

	if (!RootObject->TryGetArrayField(TEXT("Materials"), JsonMaterials))
	{
		return false;
	}

	for (const TSharedPtr<FJsonValue>& Value : *JsonMaterials)
	{
		TSharedPtr<FJsonObject> Object = Value->AsObject();

		FMaterialData Material;

		Material.MaterialName = Object->GetStringField(TEXT("material_name"));

		Material.MaterialPath = Object->GetStringField(TEXT("material_path"));

		TSharedPtr<FJsonObject> Parameters = Object->GetObjectField(TEXT("parameters"));

		const TArray<TSharedPtr<FJsonValue>>* BaseColor;

		if (Parameters->TryGetArrayField(TEXT("base_color"), BaseColor))
		{
			Material.BaseColor = FLinearColor(
				(float)(*BaseColor)[0]->AsNumber(),
				(float)(*BaseColor)[1]->AsNumber(),
				(float)(*BaseColor)[2]->AsNumber(),
				1.0f);
		}

		Material.Roughness = (float)Parameters->GetNumberField(TEXT("roughness"));

		Material.Metallic = (float)Parameters->GetNumberField(TEXT("metallic"));

		Material.Specular = (float)Parameters->GetNumberField(TEXT("specular"));

		const TArray<TSharedPtr<FJsonValue>>* Targets;

		if (Object->TryGetArrayField(TEXT("scene_targets"), Targets))
		{
			for (const TSharedPtr<FJsonValue>& Target : *Targets)
			{
				Material.SceneTargets.Add(Target->AsString());
			}
		}

		Materials.Add(Material);

		UE_LOG(LogTemp, Warning, TEXT("Material: %s"), *Material.MaterialName);
	}

	return true;
}