#include "ReviewPawn.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"

AReviewPawn::AReviewPawn()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AReviewPawn::BeginPlay()
{
    Super::BeginPlay();

    CarSeat = nullptr;
}

void AReviewPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AReviewPawn::RotateProduct(const FInputActionValue& Value)
{
    // Not used anymore.
}

void AReviewPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CarSeat == nullptr)
    {
        for (TActorIterator<AActor> It(GetWorld()); It; ++It)
        {
            if (It->GetActorLabel() == TEXT("CarSeat_FINAL"))
            {
                CarSeat = *It;
                UE_LOG(LogTemp, Warning, TEXT("CarSeat Found!"));
                break;
            }
        }

        return;
    }

    APlayerController* PC = Cast<APlayerController>(GetController());

    if (!PC)
    {
        return;
    }

    const float RotationSpeed = 80.0f;

    if (PC->IsInputKeyDown(EKeys::Left))
    {
        CarSeat->AddActorWorldRotation(FRotator(0.f, -RotationSpeed * DeltaTime, 0.f));
    }

    if (PC->IsInputKeyDown(EKeys::Right))
    {
        CarSeat->AddActorWorldRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
    }
}