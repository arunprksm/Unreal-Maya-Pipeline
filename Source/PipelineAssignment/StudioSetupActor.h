#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StudioSetupActor.generated.h"

UCLASS()
class PIPELINEASSIGNMENT_API AStudioSetupActor : public AActor
{
    GENERATED_BODY()

public:
    AStudioSetupActor();

protected:
    virtual void BeginPlay() override;

private:
    void SetupImportedModel();
};