#pragma once

#include "CoreMinimal.h"

struct FMaterialData
{
	FString MaterialName;

	FString MaterialPath;

	FLinearColor BaseColor;

	float Roughness;

	float Metallic;

	float Specular;

	TArray<FString> SceneTargets;
};