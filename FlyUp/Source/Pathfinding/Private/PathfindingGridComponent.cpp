#include "PathfindingGridComponent.h"

UPathfindingGridComponent::UPathfindingGridComponent()
: Bounds(FVector::One() * -1000, FVector::One() * 1000)
, GridNodeSize(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPathfindingGridComponent::Bake()
{
	UE_LOG(LogTemp, Warning, TEXT("Bake Pressed"));
}

