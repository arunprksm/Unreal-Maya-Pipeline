#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "ReviewPawn.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PIPELINEASSIGNMENT_API AReviewPawn : public APawn
{
    GENERATED_BODY()

public:
    AReviewPawn();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void RotateProduct(const FInputActionValue& Value);

    AActor* CarSeat;
};