#include "ReviewModeActor.h"

#include "EngineUtils.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

AReviewModeActor::AReviewModeActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AReviewModeActor::BeginPlay()
{
    Super::BeginPlay();

    EnableInput(GetWorld()->GetFirstPlayerController());
    /*if (InputComponent)
    {
        InputComponent->BindAction("RotateLeft", IE_Pressed, this, &AReviewModeActor::RotateLeft);
        InputComponent->BindAction("RotateRight", IE_Pressed, this, &AReviewModeActor::RotateRight);
    }*/

    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        if (It->GetActorLabel() == TEXT("CarSeat_FINAL"))
        {
            CarSeat = *It;
            break;
        }
    }
}

void AReviewModeActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!CarSeat)
        return;

    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    if (!PC || !CarSeat)
    {
        return;
    }

    if (PC->IsInputKeyDown(EKeys::Left))
    {
        CarSeat->AddActorLocalRotation(FRotator(0, -80 * DeltaTime, 0));
    }

    if (PC->IsInputKeyDown(EKeys::Right))
    {
        CarSeat->AddActorLocalRotation(FRotator(0, 80 * DeltaTime, 0));
    }
}

void AReviewModeActor::RotateLeft()
{
    if (!CarSeat)
        return;

    CarSeat->AddActorLocalRotation(FRotator(0.0f, -15.0f, 0.0f));
}

void AReviewModeActor::RotateRight()
{
    if (!CarSeat)
        return;

    CarSeat->AddActorLocalRotation(FRotator(0.0f, 15.0f, 0.0f));
}