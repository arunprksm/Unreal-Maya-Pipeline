#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReviewModeActor.generated.h"

UCLASS()
class PIPELINEASSIGNMENT_API AReviewModeActor : public AActor
{
    GENERATED_BODY()

public:
    AReviewModeActor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    AActor* CarSeat = nullptr;

    void RotateLeft();
    void RotateRight();
};