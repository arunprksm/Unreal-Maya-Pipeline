#include "HierarchyActor.h"

#include "Components/SceneComponent.h"

AHierarchyActor::AHierarchyActor()
{
    PrimaryActorTick.bCanEverTick = false;

    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    Root->SetMobility(EComponentMobility::Movable);

    RootComponent = Root;
}