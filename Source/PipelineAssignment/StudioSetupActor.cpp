#include "StudioSetupActor.h"

#include "EngineUtils.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

AStudioSetupActor::AStudioSetupActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AStudioSetupActor::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle TimerHandle;

    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        this,
        &AStudioSetupActor::SetupImportedModel,
        1.0f,
        false);
}

void AStudioSetupActor::SetupImportedModel()
{
    AActor* SpawnPoint = nullptr;
    AActor* CarSeat = nullptr;
    //AActor* Camera = nullptr;

    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        const FString Label = It->GetActorLabel();

        if (Label == TEXT("SM_ProductSpawnPoint"))
        {
            SpawnPoint = *It;
        }

        if (Label == TEXT("CarSeat_FINAL"))
        {
            CarSeat = *It;
        }

        /*if (Label == TEXT("Main_Camera"))
        {
            Camera = *It;
        }*/
    }

    if (SpawnPoint == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("SM_ProductSpawnPoint not found."));
        return;
    }

    if (CarSeat == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("CarSeat_FINAL not found."));
        return;
    }

    CarSeat->SetActorTransform(SpawnPoint->GetActorTransform());
    SpawnPoint->SetActorHiddenInGame(true);
    SpawnPoint->SetActorEnableCollision(false);

    /*if (Camera)
    {
        FVector CameraLocation = Camera->GetActorLocation();
        FVector TargetLocation = CarSeat->GetActorLocation();

        FRotator LookRotation =
            UKismetMathLibrary::FindLookAtRotation(CameraLocation, TargetLocation);

        Camera->SetActorRotation(LookRotation);
    }*/

    UE_LOG(LogTemp, Warning, TEXT("CarSeat moved successfully."));
}