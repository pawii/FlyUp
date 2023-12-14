#include "PathfindingGridComponent.h"

UPathfindingGridComponent::UPathfindingGridComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPathfindingGridComponent::BakeGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("Bake Pressed"));
}

void UPathfindingGridComponent::ResetGrid()
{
	Bounds = FBox(FVector::ZeroVector, FVector::OneVector * 1000);
	GridNodeSize = 100;
	
	FNodeGrid Node1;
	Node1.LocalPosition = FVector::ZeroVector;
	FNodeGrid Node2;
	Node2.LocalPosition = Node1.LocalPosition + FVector::OneVector * GridNodeSize;
	Node2.bWalkable = false;
	
	Nodes.Add(Node1);
	Nodes.Add(Node2);
}

