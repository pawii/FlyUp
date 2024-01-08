#include "PathfindingGridComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UPathfindingGridComponent::UPathfindingGridComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

FVector UPathfindingGridComponent::GetBoundsMinWorldPosition() const
{
	return Bounds.Min + GetOwner()->GetActorLocation();
}

FVector UPathfindingGridComponent::GetBoundsMaxWorldPosition() const
{
	return Bounds.Max + GetOwner()->GetActorLocation();
}

FNodeGrid UPathfindingGridComponent::FindClosestNode(FVector Location) const
{
	FVector BoundsMin = GetBoundsMinWorldPosition();
	FVector BoundsMax = GetBoundsMaxWorldPosition();
	
	int CountNodesAlongX = ((BoundsMax.X - BoundsMin.X) / GridNodeSize) + 1;
	int ClosestNodeIDAlongX = FindNodeIDAlongSpecificAxis(Location.X, BoundsMin.X, CountNodesAlongX);
	
	int CountNodesAlongY = ((BoundsMax.Y - BoundsMin.Y) / GridNodeSize) + 1;
	int ClosestNodeIDAlongY = FindNodeIDAlongSpecificAxis(Location.Y, BoundsMin.Y, CountNodesAlongY);
	
	int CountNodesAlongZ = ((BoundsMax.Z - BoundsMin.Z) / GridNodeSize) + 1;
	int ClosestNodeIDAlongZ = FindNodeIDAlongSpecificAxis(Location.Z, BoundsMin.Z, CountNodesAlongZ);

	int NodeID = ClosestNodeIDAlongZ + ClosestNodeIDAlongY * CountNodesAlongZ + ClosestNodeIDAlongX * CountNodesAlongZ * CountNodesAlongY;
	return Nodes[NodeID];
}

void UPathfindingGridComponent::FindNeighbours(const FNodeGrid& Origin, TArray<FNodeGrid>& Neigbours) const
{
	// FVector BoundsMin = GetBoundsMinWorldPosition();
	// FVector BoundsMax = GetBoundsMaxWorldPosition();
	//
	// int CountNodesAlongX = ((BoundsMax.X - BoundsMin.X) / GridNodeSize) + 1;
	// int CountNodesAlongY = ((BoundsMax.Y - BoundsMin.Y) / GridNodeSize) + 1;
	// int CountNodesAlongZ = ((BoundsMax.Z - BoundsMin.Z) / GridNodeSize) + 1;
	//
	// int OriginId = Nodes.IndexOfByKey(Origin);
	//
	// bool bHasUpNode = OriginId % CountNodesAlongZ != 0;
	// bool bHasDownNode = OriginId % CountNodesAlongZ != 1;
	// int DownNodeId = OriginId - 1;
	//
	// Neigbours.Empty();
	// Neigbours[0] = Nodes[0];
}

int UPathfindingGridComponent::FindNodeIDAlongSpecificAxis(const double& Position, const double& BoundsMin, int CountNodes) const
{
	for (int i = 0; i < CountNodes - 1; i++)
	{
		if (Position < BoundsMin + (i + 1) * GridNodeSize)
		{
			return i;
		}
	}
	return CountNodes - 1;
}

void UPathfindingGridComponent::BakeGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("Bake Pressed"));

	Nodes.Empty();
	FVector NodeHalfSize = FVector::OneVector * GridNodeSize * 0.5f;
	FVector BoundsMin = GetBoundsMinWorldPosition();
	FVector BoundsMax = GetBoundsMaxWorldPosition();

	for (float x = BoundsMin.X; x < BoundsMax.X; x+= GridNodeSize)
	{
		for (float y = BoundsMin.Y; y < BoundsMax.Y; y += GridNodeSize)
		{
			for (float z = BoundsMin.Z; z < BoundsMax.Z; z += GridNodeSize)
			{
				TArray<AActor*> ActorsToIgnore;
				FNodeGrid Node;
				Node.WorldPosition = FVector(x, y, z);
				Node.Size = GridNodeSize;
				
				FVector NodeCenter = Node.WorldPosition + FVector::One() * GridNodeSize * 0.5f;
				FHitResult HitResult;
				UKismetSystemLibrary::BoxTraceSingleByProfile(
					GetWorld(),
					NodeCenter,
					NodeCenter,
					NodeHalfSize,
					FRotator::ZeroRotator,
					FName(TEXT("PathfindingProfile")),
					true,
					ActorsToIgnore,
					EDrawDebugTrace::None,
					HitResult,
					false,
					FLinearColor::Transparent,
					FLinearColor::Transparent,
					0);
				Node.bWalkable = !HitResult.bBlockingHit;
				
				Nodes.Add(Node);
			}
		}
	}

	Modify();
}

void UPathfindingGridComponent::ResetGrid()
{
	Bounds = FBox(GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + FVector::OneVector * 1000);
	GridNodeSize = 100;
	Nodes.Empty();
	Modify();
}

void UPathfindingGridComponent::CalculatePath()
{
}
