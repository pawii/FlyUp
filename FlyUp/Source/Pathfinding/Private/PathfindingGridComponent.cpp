#include "PathfindingGridComponent.h"

UPathfindingGridComponent::UPathfindingGridComponent(): GridNodeSize(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPathfindingGridComponent::Bake()
{
	UE_LOG(LogTemp, Warning, TEXT("Bake Pressed"));
}

